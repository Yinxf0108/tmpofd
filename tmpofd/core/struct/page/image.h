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
struct border_t {
  std::optional<st_double> line_width_;
  std::optional<st_double> horizonal_corner_radius_;
  std::optional<st_double> vertical_corner_radius_;
  std::optional<st_double> dash_offset_;
  std::optional<st_array<st_double> > dash_pattern_;

  std::unique_ptr<color_t> border_color_;
};

REFLECT_STRUCT(
  ofd_namespace"Border",
  border_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("LineWidth", &border_t::line_width_),
    REFLECT_MEMBER("HorizonalCornerRadius", &border_t::horizonal_corner_radius_),
    REFLECT_MEMBER("VerticalCornerRadius", &border_t::vertical_corner_radius_),
    REFLECT_MEMBER("DashOffset", &border_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &border_t::dash_pattern_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"BorderColor", &border_t::border_color_)
  )
)

struct image_t : graphic_unit_t {
  st_ref_id resource_id_;
  std::optional<st_ref_id> substitution_;
  std::optional<st_ref_id> image_mask_;
  std::optional<border_t> border_;
};

REFLECT_STRUCT(
  ofd_namespace"Image",
  image_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Boundary", &image_t::boundary_),
    REFLECT_MEMBER("Name", &image_t::name_),
    REFLECT_MEMBER("Visible", &image_t::visible_),
    REFLECT_MEMBER("CTM", &image_t::ctm_),
    REFLECT_MEMBER("DrawParam", &image_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &image_t::line_width_),
    REFLECT_MEMBER("Cap", &image_t::cap_),
    REFLECT_MEMBER("Join", &image_t::join_),
    REFLECT_MEMBER("MiterLimit", &image_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &image_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &image_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &image_t::alpha_),
    REFLECT_MEMBER("ResourceID", &image_t::resource_id_),
    REFLECT_MEMBER("Substitution", &image_t::substitution_),
    REFLECT_MEMBER("ImageMask", &image_t::image_mask_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &image_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &image_t::clips_),
    REFLECT_MEMBER(ofd_namespace"Border", &image_t::border_)
  )
)
} // tmpofd
