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
#include "tmpofd/core/struct/page/cg_transform.h"

namespace tmpofd {
struct text_code_t {
  std::optional<st_array<st_double> > x_;
  std::optional<st_array<st_double> > y_;
  std::optional<st_array<st_double> > delta_x_;
  std::optional<st_array<st_double> > delta_y_;
  st_string leaf_value;
};

REFLECT_STRUCT(
  ofd_namespace"TextCode",
  text_code_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("X", &text_code_t::x_),
    REFLECT_MEMBER("Y", &text_code_t::y_),
    REFLECT_MEMBER("DeltaX", &text_code_t::delta_x_),
    REFLECT_MEMBER("DeltaY", &text_code_t::delta_y_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER("", &text_code_t::leaf_value)
  )
)

enum class weight_t {
  _0 = 0, _100 = 100, _200 = 200, _300 = 300, _400 = 400, _500 = 500,
  _600 = 600, _700 = 700, _800 = 800, _900 = 900, _1000 = 1000
};
template<>
struct enum_converter<weight_t> {
  static std::string to_string(const weight_t e) {
    switch (e) {
      case weight_t::_0: return "0";
      case weight_t::_100: return "100";
      case weight_t::_200: return "200";
      case weight_t::_300: return "300";
      case weight_t::_400: return "400";
      case weight_t::_500: return "500";
      case weight_t::_600: return "600";
      case weight_t::_700: return "700";
      case weight_t::_800: return "800";
      case weight_t::_900: return "900";
      case weight_t::_1000: return "1000";
    }
    return "";
  }
  static std::optional<weight_t> from_string(const std::string_view s) {
    if (s == "0") return weight_t::_0;
    if (s == "100") return weight_t::_100;
    if (s == "200") return weight_t::_200;
    if (s == "300") return weight_t::_300;
    if (s == "400") return weight_t::_400;
    if (s == "500") return weight_t::_500;
    if (s == "600") return weight_t::_600;
    if (s == "700") return weight_t::_700;
    if (s == "800") return weight_t::_800;
    if (s == "900") return weight_t::_900;
    if (s == "1000") return weight_t::_1000;
    return std::nullopt;
  }
};

struct text_t : graphic_unit_t {
  st_ref_id font_;
  st_double size_;
  std::optional<st_bool> stroke_;
  std::optional<st_bool> fill_;
  std::optional<st_double> h_scale_;
  std::optional<st_int> read_direction_;
  std::optional<st_int> char_direction_;
  std::optional<enum_string_t<weight_t> > weight_;
  std::optional<st_bool> italic_;
  std::unique_ptr<color_t> fill_color_;
  std::unique_ptr<color_t> stroke_color_;
  st_vector<cg_transform_t> cg_transform_;
  st_vector<text_code_t> text_code_;
};

REFLECT_STRUCT(
  ofd_namespace"Text",
  text_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Boundary", &text_t::boundary_),
    REFLECT_MEMBER("Name", &text_t::name_),
    REFLECT_MEMBER("Visible", &text_t::visible_),
    REFLECT_MEMBER("CTM", &text_t::ctm_),
    REFLECT_MEMBER("DrawParam", &text_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &text_t::line_width_),
    REFLECT_MEMBER("Cap", &text_t::cap_),
    REFLECT_MEMBER("Join", &text_t::join_),
    REFLECT_MEMBER("MiterLimit", &text_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &text_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &text_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &text_t::alpha_),
    REFLECT_MEMBER("Font", &text_t::font_),
    REFLECT_MEMBER("Size", &text_t::size_),
    REFLECT_MEMBER("Stroke", &text_t::stroke_),
    REFLECT_MEMBER("Fill", &text_t::fill_),
    REFLECT_MEMBER("HScale", &text_t::h_scale_),
    REFLECT_MEMBER("ReadDirection", &text_t::read_direction_),
    REFLECT_MEMBER("CharDirection", &text_t::char_direction_),
    REFLECT_MEMBER("Weight", &text_t::weight_),
    REFLECT_MEMBER("Italic", &text_t::italic_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &text_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &text_t::clips_),
    REFLECT_MEMBER(ofd_namespace"FillColor", &text_t::fill_color_),
    REFLECT_MEMBER(ofd_namespace"StrokeColor", &text_t::stroke_color_),
    REFLECT_MEMBER(ofd_namespace"CGTransform", &text_t::cg_transform_),
    REFLECT_MEMBER(ofd_namespace"TextCode", &text_t::text_code_)
  )
)
} // tmpofd
