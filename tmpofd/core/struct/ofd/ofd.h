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

#include "tmpofd/core/struct/ofd/doc_body.h"

namespace tmpofd {
enum class doc_type_t { OFD };
template<>
struct enum_converter<doc_type_t> {
  static std::string to_string(doc_type_t) { return "OFD"; }
  static std::optional<doc_type_t> from_string(const std::string_view s) {
    if (s == "OFD") return doc_type_t::OFD;
    return std::nullopt;
  }
};

struct ofd_t {
  std::optional<st_string> namespace_;
  st_string version_;
  enum_string_t<doc_type_t> doc_type_;

  st_vector<doc_body_t> doc_body_;
};

REFLECT_STRUCT(
  ofd_namespace"OFD",
  ofd_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &ofd_t::namespace_),
    REFLECT_MEMBER("Version", &ofd_t::version_),
    REFLECT_MEMBER("DocType", &ofd_t::doc_type_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"DocBody", &ofd_t::doc_body_)
  )
)
} // tmpofd
