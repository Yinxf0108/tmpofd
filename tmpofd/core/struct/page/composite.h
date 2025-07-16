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
struct composite_t : graphic_unit_t {
  st_ref_id resource_id_;
};

REFLECT_STRUCT(
  ofd_namespace"Composite",
  composite_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Boundary", &composite_t::boundary_),
    REFLECT_MEMBER("Name", &composite_t::name_),
    REFLECT_MEMBER("Visible", &composite_t::visible_),
    REFLECT_MEMBER("CTM", &composite_t::ctm_),
    REFLECT_MEMBER("DrawParam", &composite_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &composite_t::line_width_),
    REFLECT_MEMBER("Cap", &composite_t::cap_),
    REFLECT_MEMBER("Join", &composite_t::join_),
    REFLECT_MEMBER("MiterLimit", &composite_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &composite_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &composite_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &composite_t::alpha_),
    REFLECT_MEMBER("ResourceID", &composite_t::resource_id_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &composite_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &composite_t::clips_)
  )
)
} // tmpofd
