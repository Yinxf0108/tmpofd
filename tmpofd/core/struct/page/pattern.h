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

#include "tmpofd/core/struct/common/complex_type.h"
#include "tmpofd/core/struct/page/page_block.h"

namespace tmpofd {
enum class reflect_method_t { Normal, Row, Column, RowAndColumn };
template<>
struct enum_converter<reflect_method_t> {
  static std::string to_string(const reflect_method_t e) {
    switch (e) {
      case reflect_method_t::Normal: return "Normal";
      case reflect_method_t::Row: return "Row";
      case reflect_method_t::Column: return "Column";
      case reflect_method_t::RowAndColumn: return "RowAndColumn";
    }
    return "";
  }
  static std::optional<reflect_method_t> from_string(const std::string_view s) {
    if (s == "Normal") return reflect_method_t::Normal;
    if (s == "Row") return reflect_method_t::Row;
    if (s == "Column") return reflect_method_t::Column;
    if (s == "RowAndColumn") return reflect_method_t::RowAndColumn;
    return std::nullopt;
  }
};

enum class relative_to_t { Page, Object };
template<>
struct enum_converter<relative_to_t> {
  static std::string to_string(const relative_to_t e) {
    switch (e) {
      case relative_to_t::Page: return "Page";
      case relative_to_t::Object: return "Object";
    }
    return "";
  }
  static std::optional<relative_to_t> from_string(const std::string_view s) {
    if (s == "Page") return relative_to_t::Page;
    if (s == "Object") return relative_to_t::Object;
    return std::nullopt;
  }
};

struct cell_content_t {
  std::optional<st_ref_id> thumbnail_;
  std::vector<page_block_op_t> page_block_ops_;
};

REFLECT_STRUCT(
  ofd_namespace"CellContent",
  cell_content_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Thumbnail", &cell_content_t::thumbnail_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"TextObject", &cell_content_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"PathObject", &cell_content_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"ImageObject", &cell_content_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"CompositeObject", &cell_content_t::page_block_ops_),
    REFLECT_MEMBER(ofd_namespace"PageBlock", &cell_content_t::page_block_ops_)
  )
)

struct pattern_t {
  st_double width_;
  st_double height_;
  std::optional<st_double> x_step_;
  std::optional<st_double> y_step_;
  std::optional<enum_string_t<reflect_method_t> > reflect_method_;
  std::optional<enum_string_t<relative_to_t> > relative_to_;
  std::optional<st_array<st_double> > ctm_;
  cell_content_t cell_content_;
};
REFLECT_STRUCT(
  ofd_namespace"Pattern",
  pattern_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Width", &pattern_t::width_),
    REFLECT_MEMBER("Height", &pattern_t::height_),
    REFLECT_MEMBER("XStep", &pattern_t::x_step_),
    REFLECT_MEMBER("YStep", &pattern_t::y_step_),
    REFLECT_MEMBER("ReflectMethod", &pattern_t::reflect_method_),
    REFLECT_MEMBER("RelativeTo", &pattern_t::relative_to_),
    REFLECT_MEMBER("CTM", &pattern_t::ctm_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"CellContent", &pattern_t::cell_content_)
  )
)
} // tmpofd
