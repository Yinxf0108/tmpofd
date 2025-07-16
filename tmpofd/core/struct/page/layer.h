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

#include "tmpofd/core/struct/page/page_block.h"

namespace tmpofd {
enum class layer_type_t { Body, Background, Foreground, Custom };
template<>
struct enum_converter<layer_type_t> {
  static std::string to_string(const layer_type_t e) {
    switch (e) {
      case layer_type_t::Body: return "Body";
      case layer_type_t::Background: return "Background";
      case layer_type_t::Foreground: return "Foreground";
      case layer_type_t::Custom: return "Custom";
    }
    return "";
  }
  static std::optional<layer_type_t> from_string(const std::string_view s) {
    if (s == "Body") return layer_type_t::Body;
    if (s == "Background") return layer_type_t::Background;
    if (s == "Foreground") return layer_type_t::Foreground;
    if (s == "Custom") return layer_type_t::Custom;
    return std::nullopt;
  }
};

struct layer_t {
  st_id id_;
  std::optional<enum_string_t<layer_type_t> > type_;
  std::optional<st_ref_id> draw_param_;
  st_vector<page_block_t> page_block_ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Layer",
  layer_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &layer_t::id_),
    REFLECT_MEMBER("Type", &layer_t::type_),
    REFLECT_MEMBER("DrawParam", &layer_t::draw_param_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"TextObject", &layer_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"PathObject", &layer_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"ImageObject", &layer_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"CompositeObject", &layer_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"PageBlock", &layer_t::page_block_ops_)
  )
)
} // tmpofd
