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
struct axial_shd_t {
  std::optional<enum_string_t<map_type_t> > map_type_;
  std::optional<st_double> map_unit_;
  std::optional<extend_t> extend_;
  st_pos<st_double> start_point_;
  st_pos<st_double> end_point_;
  std::vector<segment_t> segments_;
};

REFLECT_STRUCT(
  ofd_namespace"AxialShd",
  axial_shd_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("MapType", &axial_shd_t::map_type_),
    REFLECT_MEMBER("MapUnit", &axial_shd_t::map_unit_),
    REFLECT_MEMBER("Extend", &axial_shd_t::extend_),
    REFLECT_MEMBER("StartPoint", &axial_shd_t::start_point_),
    REFLECT_MEMBER("EndPoint", &axial_shd_t::end_point_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Segment", &axial_shd_t::segments_)
  )
)
} // tmpofd
