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

#include "tmpofd/core/reflection/reflection.h"

namespace tmpofd {
enum class signature_type_t { Seal, Sign };
template<>
struct enum_converter<signature_type_t> {
  static std::string to_string(const signature_type_t e) {
    switch (e) {
      case signature_type_t::Seal: return "Seal";
      case signature_type_t::Sign: return "Sign";
    }
    return "";
  }
  static std::optional<signature_type_t> from_string(const std::string_view s) {
    if (s == "Seal") return signature_type_t::Seal;
    if (s == "Sign") return signature_type_t::Sign;
    return std::nullopt;
  }
};

struct signature_info_t {
  st_id id_;
  std::optional<enum_string_t<signature_type_t> > type_;
  st_loc base_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"Signature",
  signature_info_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &signature_info_t::id_),
    REFLECT_MEMBER("Type", &signature_info_t::type_),
    REFLECT_MEMBER("BaseLoc", &signature_info_t::base_loc_)
  )
  REFLECT_NODE()
)

struct signatures_t {
  std::optional<st_string> namespace_;
  std::optional<st_id> max_sign_id_;
  st_vector<signature_info_t> signature_;
};

REFLECT_STRUCT(
  ofd_namespace"Signatures",
  signatures_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &signatures_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"MaxSignId", &signatures_t::max_sign_id_),
    REFLECT_MEMBER(ofd_namespace"Signature", &signatures_t::signature_)
  )
)
} // tmpofd
