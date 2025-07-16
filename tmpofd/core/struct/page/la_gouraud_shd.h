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
struct la_gouraud_point_t {
  st_double x_;
  st_double y_;
  std::unique_ptr<color_t> color_;
};

REFLECT_STRUCT(
  ofd_namespace"Point",
  la_gouraud_point_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("X", &la_gouraud_point_t::x_),
    REFLECT_MEMBER("Y", &la_gouraud_point_t::y_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Color", &la_gouraud_point_t::color_)
  )
)

struct la_gouraud_shd_t {
  st_int vertices_per_row_;
  std::optional<extend_t> extend_;
  std::vector<la_gouraud_point_t> point_;
  std::unique_ptr<color_t> back_color_;
};

REFLECT_STRUCT(
  ofd_namespace"LaGourandShd",
  la_gouraud_shd_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("VerticesPerRow", &la_gouraud_shd_t::vertices_per_row_),
    REFLECT_MEMBER("Extend", &la_gouraud_shd_t::extend_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Point", &la_gouraud_shd_t::point_),
    REFLECT_MEMBER(ofd_namespace"BackColor", &la_gouraud_shd_t::back_color_)
  )
)
} // tmpofd
