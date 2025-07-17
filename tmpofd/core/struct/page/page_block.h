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

#include "tmpofd/core/struct/page/text.h"
#include "tmpofd/core/struct/page/path.h"
#include "tmpofd/core/struct/page/image.h"
#include "tmpofd/core/struct/page/composite.h"

namespace tmpofd {
struct page_block_t;

struct _text_t : text_t {
  st_id id_{};
};

REFLECT_STRUCT(
  ofd_namespace"TextObject",
  _text_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &_text_t::id_),
    REFLECT_MEMBER("Boundary", &_text_t::boundary_),
    REFLECT_MEMBER("Name", &_text_t::name_),
    REFLECT_MEMBER("Visible", &_text_t::visible_),
    REFLECT_MEMBER("CTM", &_text_t::ctm_),
    REFLECT_MEMBER("DrawParam", &_text_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &_text_t::line_width_),
    REFLECT_MEMBER("Cap", &_text_t::cap_),
    REFLECT_MEMBER("Join", &_text_t::join_),
    REFLECT_MEMBER("MiterLimit", &_text_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &_text_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &_text_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &_text_t::alpha_),
    REFLECT_MEMBER("Font", &_text_t::font_),
    REFLECT_MEMBER("Size", &_text_t::size_),
    REFLECT_MEMBER("Stroke", &_text_t::stroke_),
    REFLECT_MEMBER("Fill", &_text_t::fill_),
    REFLECT_MEMBER("HScale", &_text_t::h_scale_),
    REFLECT_MEMBER("ReadDirection", &_text_t::read_direction_),
    REFLECT_MEMBER("CharDirection", &_text_t::char_direction_),
    REFLECT_MEMBER("Weight", &_text_t::weight_),
    REFLECT_MEMBER("Italic", &_text_t::italic_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &_text_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &_text_t::clips_),
    REFLECT_MEMBER(ofd_namespace"FillColor", &_text_t::fill_color_),
    REFLECT_MEMBER(ofd_namespace"StrokeColor", &_text_t::stroke_color_),
    REFLECT_MEMBER(ofd_namespace"CGTransform", &_text_t::cg_transform_),
    REFLECT_MEMBER(ofd_namespace"TextCode", &_text_t::text_code_)
  )
)

struct _path_t : path_t {
  st_id id_{};
};

REFLECT_STRUCT(
  ofd_namespace"PathObject",
  _path_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &_path_t::id_),
    REFLECT_MEMBER("Boundary", &_path_t::boundary_),
    REFLECT_MEMBER("Name", &_path_t::name_),
    REFLECT_MEMBER("Visible", &_path_t::visible_),
    REFLECT_MEMBER("CTM", &_path_t::ctm_),
    REFLECT_MEMBER("DrawParam", &_path_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &_path_t::line_width_),
    REFLECT_MEMBER("Cap", &_path_t::cap_),
    REFLECT_MEMBER("Join", &_path_t::join_),
    REFLECT_MEMBER("MiterLimit", &_path_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &_path_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &_path_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &_path_t::alpha_),
    REFLECT_MEMBER("Stroke", &_path_t::stroke_),
    REFLECT_MEMBER("Fill", &_path_t::fill_),
    REFLECT_MEMBER("Rule", &_path_t::rule_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &_path_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &_path_t::clips_),
    REFLECT_MEMBER(ofd_namespace"StrokeColor", &_path_t::stroke_color_),
    REFLECT_MEMBER(ofd_namespace"FillColor", &_path_t::fill_color_),
    REFLECT_MEMBER(ofd_namespace"AbbreviatedData", &_path_t::abbreviated_data_)
  )
)
struct _image_t : image_t {
  st_id id_{};
};

REFLECT_STRUCT(
  ofd_namespace"ImageObject",
  _image_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &_image_t::id_),
    REFLECT_MEMBER("Boundary", &_image_t::boundary_),
    REFLECT_MEMBER("Name", &_image_t::name_),
    REFLECT_MEMBER("Visible", &_image_t::visible_),
    REFLECT_MEMBER("CTM", &_image_t::ctm_),
    REFLECT_MEMBER("DrawParam", &_image_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &_image_t::line_width_),
    REFLECT_MEMBER("Cap", &_image_t::cap_),
    REFLECT_MEMBER("Join", &_image_t::join_),
    REFLECT_MEMBER("MiterLimit", &_image_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &_image_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &_image_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &_image_t::alpha_),
    REFLECT_MEMBER("ResourceID", &_image_t::resource_id_),
    REFLECT_MEMBER("Substitution", &_image_t::substitution_),
    REFLECT_MEMBER("ImageMask", &_image_t::image_mask_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &_image_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &_image_t::clips_),
    REFLECT_MEMBER(ofd_namespace"Border", &_image_t::border_)
  )
)

struct _composite_t : composite_t {
  st_id id_{};
};

REFLECT_STRUCT(
  ofd_namespace"CompositeObject",
  _composite_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &_composite_t::id_),
    REFLECT_MEMBER("Boundary", &_composite_t::boundary_),
    REFLECT_MEMBER("Name", &_composite_t::name_),
    REFLECT_MEMBER("Visible", &_composite_t::visible_),
    REFLECT_MEMBER("CTM", &_composite_t::ctm_),
    REFLECT_MEMBER("DrawParam", &_composite_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &_composite_t::line_width_),
    REFLECT_MEMBER("Cap", &_composite_t::cap_),
    REFLECT_MEMBER("Join", &_composite_t::join_),
    REFLECT_MEMBER("MiterLimit", &_composite_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &_composite_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &_composite_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &_composite_t::alpha_),
    REFLECT_MEMBER("ResourceID", &_composite_t::resource_id_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &_composite_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &_composite_t::clips_)
  )
)

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(page_block_op_t, _text_t, _path_t, _image_t, _composite_t, std:: unique_ptr<page_block_t >),
  DEFINE_VARIANT_TYPE(_text_t, ofd_namespace"TextObject")
  DEFINE_VARIANT_TYPE(_path_t, ofd_namespace"PathObject")
  DEFINE_VARIANT_TYPE(_image_t, ofd_namespace"ImageObject")
  DEFINE_VARIANT_TYPE(_composite_t, ofd_namespace"CompositeObject")
  DEFINE_VARIANT_TYPE(std::unique_ptr<page_block_t>, ofd_namespace"PageBlock")
)

struct page_block_t {
  st_id id_{};
  st_vector<page_block_op_t> ops_;
};

REFLECT_STRUCT(
  ofd_namespace"PageBlock",
  page_block_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &page_block_t::id_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"TextObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PathObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"ImageObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"CompositeObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PageBlock", &page_block_t::ops_)
  )
)
} // tmpofd
