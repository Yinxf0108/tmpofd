/**
*** MIT License
*** 
*** Copyright (c) 2025 Yinxf
*** 
*** Permission is hereby granted, free of charge, to any person obtaining a copy
*** of this software and associated documentation files (the "Software"), to deal
*** in the Software without restriction, including without limitation the rights
*** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*** copies of the Software, and to permit persons to whom the Software is
*** furnished to do so, subject to the following conditions:
*** 
*** The above copyright notice and this permission notice shall be included in all
*** copies or substantial portions of the Software.
*** 
*** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*** SOFTWARE.
**/

#pragma once

#include "tmpofd/core/struct/common/simple_type_fwd.h"

#include "zip.h"

#include <string>
#include <stdexcept>

namespace tmpofd {
struct ZipHandler {
  static ZipHandler &ins() {
    static ZipHandler instance;
    return instance;
  }

  void load(const std::string &file_path) {
    close();

    int ret = 0;
    archive_ = zip_open(file_path.c_str(), 0, &ret);
    if (nullptr == archive_) {
      zip_error_t error;
      zip_error_init_with_code(&error, ret);

      throw std::runtime_error("Failed to load '" + file_path + "': " + zip_error_strerror(&error));
    }
  }

  [[nodiscard]] std::string get(const st_loc &entry_path) const {
    if (nullptr == archive_) {
      throw std::runtime_error("No file loaded. Call load() first.");
    }

    struct zip_stat st{};
    zip_stat_init(&st);
    if (0 != zip_stat(archive_, entry_path.generic_string().c_str(), 0, &st)) {
      throw std::runtime_error("Cannot stat '" + entry_path.generic_string() + "': " + zip_strerror(archive_));
    }

    zip_file_t *zf = zip_fopen(archive_, entry_path.generic_string().c_str(), 0);
    if (nullptr == zf) {
      throw std::runtime_error("Failed to open '" + entry_path.generic_string() + "': " + zip_strerror(archive_));
    }

    std::string content;
    content.resize(st.size);
    const zip_int64_t bytes_read = zip_fread(zf, &content[0], st.size);

    zip_fclose(zf);

    if (0 > bytes_read || st.size != static_cast<zip_uint64_t>(bytes_read)) {
      throw std::runtime_error("Failed to read '" + entry_path.generic_string() + "'.");
    }

    return content;
  }

  void close() {
    if (nullptr != archive_) {
      zip_close(archive_);
      archive_ = nullptr;
    }
  }

  ZipHandler(const ZipHandler &) = delete;
  ZipHandler &operator=(const ZipHandler &) = delete;
  ZipHandler(ZipHandler &&) = delete;
  ZipHandler &operator=(ZipHandler &&) = delete;

  private:
    ZipHandler() = default;
    ~ZipHandler() { close(); }

    zip_t *archive_ = nullptr;
};
} // tmpofd
