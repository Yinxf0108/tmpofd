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

#include "tmpofd/core/struct/page/pattern.h"
#include "tmpofd/core/struct/page/axial_shd.h"
#include "tmpofd/core/struct/page/radial_shd.h"
#include "tmpofd/core/struct/page/gouraud_shd.h"
#include "tmpofd/core/struct/page/la_gouraud_shd.h"

namespace tmpofd {
DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(complex_color_op_t, pattern_t, axial_shd_t, radial_shd_t, gouraud_shd_t, la_gouraud_shd_t),
  DEFINE_VARIANT_TYPE(pattern_t, ofd_namespace"Pattern")
  DEFINE_VARIANT_TYPE(axial_shd_t, ofd_namespace"AxialShd")
  DEFINE_VARIANT_TYPE(radial_shd_t, ofd_namespace"RadialShd")
  DEFINE_VARIANT_TYPE(gouraud_shd_t, ofd_namespace"GouraudShd")
  DEFINE_VARIANT_TYPE(la_gouraud_shd_t, ofd_namespace"LaGourandShd")
)

struct color_t {
  std::optional<st_array<st_int> > value_;
  std::optional<st_int> index_;
  std::optional<st_ref_id> color_space_;
  std::optional<st_int> alpha_;
  std::optional<complex_color_op_t> complex_color_ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Color",
  color_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Value", &color_t::value_),
    REFLECT_MEMBER("Index", &color_t::index_),
    REFLECT_MEMBER("ColorSpace", &color_t::color_space_),
    REFLECT_MEMBER("Alpha", &color_t::alpha_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Pattern", &color_t::complex_color_ops_),
    REFLECT_MEMBER(ofd_namespace"AxialShd", &color_t::complex_color_ops_),
    REFLECT_MEMBER(ofd_namespace"RadialShd", &color_t::complex_color_ops_),
    REFLECT_MEMBER(ofd_namespace"GouraudShd", &color_t::complex_color_ops_),
    REFLECT_MEMBER(ofd_namespace"LaGourandShd", &color_t::complex_color_ops_)
  )
)
} // tmpofd
