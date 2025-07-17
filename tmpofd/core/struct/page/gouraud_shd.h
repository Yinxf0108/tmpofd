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

namespace tmpofd {
enum class edge_flag_t { EdgeFlag0, EdgeFlag1, EdgeFlag2 };
template<>
struct enum_converter<edge_flag_t> {
  static std::string to_string(const edge_flag_t e) {
    switch (e) {
      case edge_flag_t::EdgeFlag0: return "0";
      case edge_flag_t::EdgeFlag1: return "1";
      case edge_flag_t::EdgeFlag2: return "2";
    }
    return "";
  }
  static std::optional<edge_flag_t> from_string(const std::string_view s) {
    if (s == "0") return edge_flag_t::EdgeFlag0;
    if (s == "1") return edge_flag_t::EdgeFlag1;
    if (s == "2") return edge_flag_t::EdgeFlag2;
    return std::nullopt;
  }
};

struct gouraud_point_t {
  st_double x_;
  st_double y_;
  std::optional<enum_string_t<edge_flag_t> > edge_flag_;
  std::unique_ptr<color_t> color_;
};

REFLECT_STRUCT(
  ofd_namespace"Point",
  gouraud_point_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("X", &gouraud_point_t::x_),
    REFLECT_MEMBER("Y", &gouraud_point_t::y_),
    REFLECT_MEMBER("EdgeFlag", &gouraud_point_t::edge_flag_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Color", &gouraud_point_t::color_)
  )
)

struct gouraud_shd_t {
  std::optional<enum_string_t<extend_t> > extend_;
  std::vector<gouraud_point_t> point_;
  std::unique_ptr<color_t> back_color_;
};

REFLECT_STRUCT(
  ofd_namespace"GouraudShd",
  gouraud_shd_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Extend", &gouraud_shd_t::extend_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Point", &gouraud_shd_t::point_),
    REFLECT_MEMBER(ofd_namespace"BackColor", &gouraud_shd_t::back_color_)
  )
)
} // tmpofd
