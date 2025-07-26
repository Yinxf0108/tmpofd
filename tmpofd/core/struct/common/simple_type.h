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

#include "tmpofd/core/traits/type_traits.h"

#include <cassert>

namespace tmpofd {
/**
* 数组，以空格来分割元素。元素可以是除st_loc、st_array外的数据类型，不可嵌套
*/
template<typename T> requires (!std::same_as<st_loc, std::remove_cvref_t<T> > && !is_vector<T>)
struct st_array {
  using value_type = typename st_vector<T>::value_type;
  using iterator = typename st_vector<T>::iterator;
  using const_iterator = typename st_vector<T>::const_iterator;

  st_array() = default;
  st_array(std::initializer_list<T> init) : data_(init) {}

  void from_string(const std::string_view str, const char sep = ' ') {
    data_.clear();
    reset_compression_state();

    std::string s(str);
    if (' ' != sep) {
      for (char &ch : s) {
        if (sep == ch) {
          ch = ' ';
        }
      }
    }
    std::stringstream ss(s);

    std::string token;
    bool compressed = false;
    while (ss >> token) {
      if ("g" == token) {
        compressed = true;

        std::string count_str, value_str;
        if (!(ss >> count_str) || !(ss >> value_str)) {
          throw std::runtime_error("Malformed 'g' operator in st_array: requires count and value.");
        }

        try {
          size_t count = std::stoull(count_str);
          T value;
          if constexpr (is_floating_t<T>) { value.from_string(value_str); } else {
            std::stringstream(value_str) >> value;
          }
          data_.insert(data_.end(), count, value);
        } catch (const std::exception &e) {
          throw std::invalid_argument(std::string("Failed to parse 'g' operator arguments in st_array: ") + e.what());
        }

        continue;
      }

      T value;
      if constexpr (is_floating_t<T>) { value.from_string(token); } else { std::stringstream(token) >> value; }
      data_.push_back(std::move(value));
    }

    if (compressed) {
      compression_state_ = CompressionState::Compressed;
      original_compressed_string_ = str;
    } else {
      compression_state_ = CompressionState::Uncompressed;
    }
  }

  [[nodiscard]] std::string to_string(const char sep = ' ') const {
    if (data_.empty())
      return "";

    switch (compression_state_) {
      case CompressionState::Compressed:
        return *original_compressed_string_;
      case CompressionState::Uncompressed:
        break;
      case CompressionState::Unknown: {
        st_vector<std::string> tokens;

        size_t i = 0;
        while (i < data_.size()) {
          size_t j = i;
          while (j < data_.size() && data_[j] == data_[i]) {
            j++;
          }
          const size_t count = j - i;
          const auto &value = data_[i];

          std::stringstream ss;
          if (count >= 2) {
            ss << "g " << count << " ";
            if constexpr (is_floating_t<T>) ss << value.to_string();
            else ss << value;
          } else {
            if constexpr (is_floating_t<T>) ss << value.to_string();
            else ss << value;
          }
          tokens.push_back(ss.str());

          i = j;
        }

        std::stringstream final_ss;
        for (size_t k = 0; k < tokens.size(); ++k) {
          final_ss << tokens[k] << (k < tokens.size() - 1 ? std::string(1, sep) : "");
        }

        return final_ss.str();
      }
    }

    std::stringstream ss;
    for (size_t i = 0; i < data_.size(); ++i) {
      if constexpr (is_floating_t<T>) {
        ss << data_[i].to_string();
      } else {
        ss << data_[i];
      }
      if (i < data_.size() - 1) {
        ss << sep;
      }
    }

    return ss.str();
  }

  auto begin() { return data_.begin(); }
  auto end() { return data_.end(); }
  auto begin() const { return data_.begin(); }
  auto end() const { return data_.end(); }

  auto size() const { return data_.size(); }
  auto empty() const { return data_.empty(); }

  auto &operator[](size_t index) { return data_[index]; }
  const auto &operator[](size_t index) const { return data_[index]; }

  void push_back(const T &value) {
    data_.push_back(value);
    reset_compression_state();
  }
  void push_back(T &&value) {
    data_.push_back(std::move(value));
    reset_compression_state();
  }

  template<typename... Args>
  void emplace_back(Args &&... args) {
    data_.emplace_back(std::forward<Args>(args)...);
    reset_compression_state();
  }

  private:
    st_vector<T> data_;

    enum class CompressionState {
      Unknown,
      Uncompressed,
      Compressed
    };

    CompressionState compression_state_ = CompressionState::Unknown;

    std::optional<std::string> original_compressed_string_;

    void reset_compression_state() {
      compression_state_ = CompressionState::Unknown;
      original_compressed_string_.reset();
    }
};

/**
* 标识，在simple_type_fwd.h中声明
*/

/**
* 标识引用，在simple_type_fwd.h中声明
*/

/**
* 点坐标，以空格分割，前者为x值，后者为y值，可以是整数或者浮点数
*/
template<is_st_number T>
struct st_pos {
  T x_;
  T y_;

  constexpr st_pos() : x_(T{}), y_(T{}) {}
  constexpr st_pos(T x, T y) : x_(x), y_(y) {}

  void from_string(const std::string_view str, const char sep = ' ') {
    std::string s(str);
    if (' ' != sep) {
      for (char &ch : s) {
        if (sep == ch) {
          ch = ' ';
        }
      }
    }
    std::stringstream ss(s);

    if constexpr (is_floating_t<T>) {
      std::string x, y;
      ss >> x >> y;
      x_ = x;
      y_ = y;
    } else {
      ss >> x_ >> y_;
    }
  }

  [[nodiscard]] std::string to_string(char sep = ' ') const {
    std::stringstream ss;

    if constexpr (is_floating_t<T>) {
      ss << x_.to_string() << sep << y_.to_string();
    } else {
      ss << x_ << sep << y_;
    }

    return ss.str();
  }

  auto operator<=>(const st_pos &) const = default;
};

/**
* 矩形区域，以空格分割，前两个值代表了该矩形的左上角的坐标，后两个值依次表示该矩形的宽和高，可以是整数或者浮点数，后两个值应大于0
*/
template<is_st_number T>
struct st_box {
  T x_;
  T y_;
  T width_;
  T height_;

  constexpr st_box() : x_(T{}), y_(T{}), width_(T{}), height_(T{}) {}

  constexpr st_box(T x, T y, T width, T height)
    : x_(x), y_(y), width_(width), height_(height) {
    assert(width_ > 0 && height_ > 0 && "st_box: width and height must be positive.");
  }

  void from_string(const std::string_view str, const char sep = ' ') {
    std::string s(str);
    if (' ' != sep) {
      for (char &ch : s) {
        if (sep == ch) {
          ch = ' ';
        }
      }
    }
    std::stringstream ss(s);

    if constexpr (is_floating_t<T>) {
      std::string x, y, width, height;
      ss >> x >> y >> width >> height;
      x_ = x;
      y_ = y;
      width_ = width;
      height_ = height;
    } else {
      ss >> x_ >> y_ >> width_ >> height_;
    }

    assert(width_ > 0 && height_ > 0 && "st_box: width and height must be positive.");
  }

  [[nodiscard]] std::string to_string(char sep = ' ') const {
    std::stringstream ss;

    if constexpr (is_floating_t<T>) {
      ss << x_.to_string() << sep << y_.to_string() << sep << width_.to_string() << sep << height_.to_string();
    } else {
      ss << x_ << sep << y_ << sep << width_ << sep << height_;
    }

    return ss.str();
  }

  auto operator<=>(const st_box &) const = default;
};
} // tmpofd
