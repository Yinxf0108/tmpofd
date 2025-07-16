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
#include "tmpofd/core/struct/page/color.h"
#include "tmpofd/core/struct/page/cg_transform.h"

namespace tmpofd {
struct text_code_t {};

enum class weight_t {
  _100 = 100, _200 = 200, _300 = 300, _400 = 400, _500 = 500,
  _600 = 600, _700 = 700, _800 = 800, _900 = 900
};
template<>
struct enum_converter<weight_t> {
  static std::string to_string(const weight_t e) {
    switch (e) {
      case weight_t::_100: return "100";
      case weight_t::_200: return "200";
      case weight_t::_300: return "300";
      case weight_t::_400: return "400";
      case weight_t::_500: return "500";
      case weight_t::_600: return "600";
      case weight_t::_700: return "700";
      case weight_t::_800: return "800";
      case weight_t::_900: return "900";
    }
    return "";
  }
  static std::optional<weight_t> from_string(const std::string_view s) {
    if (s == "100") return weight_t::_100;
    if (s == "200") return weight_t::_200;
    if (s == "300") return weight_t::_300;
    if (s == "400") return weight_t::_400;
    if (s == "500") return weight_t::_500;
    if (s == "600") return weight_t::_600;
    if (s == "700") return weight_t::_700;
    if (s == "800") return weight_t::_800;
    if (s == "900") return weight_t::_900;
    return std::nullopt;
  }
};

struct text_t final : graphic_unit_t {
  st_ref_id font_;
  st_double size_;
  std::optional<st_bool> stroke_;
  std::optional<st_bool> fill_;
  std::optional<st_double> h_scale_;
  std::optional<st_int> read_direction_;
  std::optional<st_int> char_direction_;
  std::optional<enum_string_t<weight_t> > weight_;
  std::optional<st_bool> italic_;
  std::optional<color_t> fill_color_;
  std::optional<color_t> stroke_color_;
  st_vector<cg_transform_t> cg_transform_;
  st_vector<text_code_t> text_code_;
};
} // tmpofd
