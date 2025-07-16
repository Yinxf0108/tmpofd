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

#include "tmpofd/core/struct/page/graphic_unit.h"

namespace tmpofd {
enum class rule_type_t { NonZero, EvenOdd };
template<>
struct enum_converter<rule_type_t> {
  static std::string to_string(const rule_type_t e) {
    switch (e) {
      case rule_type_t::NonZero: return "NonZero";
      case rule_type_t::EvenOdd: return "Even-Odd";
    }
    return "";
  }
  static std::optional<rule_type_t> from_string(const std::string_view s) {
    if (s == "NonZero") return rule_type_t::NonZero;
    if (s == "Even-Odd") return rule_type_t::EvenOdd;
    return std::nullopt;
  }
};

struct path_t : graphic_unit_t {
  std::optional<st_bool> stroke_;
  std::optional<st_bool> fill_;
  std::optional<enum_string_t<rule_type_t> > rule_;
  std::unique_ptr<color_t> stroke_color_;
  std::unique_ptr<color_t> fill_color_;
  st_string abbreviated_data_;
};

REFLECT_STRUCT(
  ofd_namespace"Path",
  path_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Boundary", &path_t::boundary_),
    REFLECT_MEMBER("Name", &path_t::name_),
    REFLECT_MEMBER("Visible", &path_t::visible_),
    REFLECT_MEMBER("CTM", &path_t::ctm_),
    REFLECT_MEMBER("DrawParam", &path_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &path_t::line_width_),
    REFLECT_MEMBER("Cap", &path_t::cap_),
    REFLECT_MEMBER("Join", &path_t::join_),
    REFLECT_MEMBER("MiterLimit", &path_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &path_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &path_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &path_t::alpha_),
    REFLECT_MEMBER("Stroke", &path_t::stroke_),
    REFLECT_MEMBER("Fill", &path_t::fill_),
    REFLECT_MEMBER("Rule", &path_t::rule_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &path_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &path_t::clips_),
    REFLECT_MEMBER(ofd_namespace"StrokeColor", &path_t::stroke_color_),
    REFLECT_MEMBER(ofd_namespace"FillColor", &path_t::fill_color_),
    REFLECT_MEMBER(ofd_namespace"AbbreviatedData", &path_t::abbreviated_data_)
  )
)
} // tmpofd
