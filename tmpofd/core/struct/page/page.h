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

#include "tmpofd/core/struct/page/layer.h"

namespace tmpofd {
struct _template_t {
  st_ref_id template_id_{};
  std::optional<enum_string_t<z_order_t> > z_order_;
};

REFLECT_STRUCT(
  ofd_namespace"Template",
  _template_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("TemplateID", &_template_t::template_id_),
    REFLECT_MEMBER("ZOrder", &_template_t::z_order_)
  )
  REFLECT_NODE()
)

struct content_t {
  st_vector<layer_t> layer_;
};

REFLECT_STRUCT(
  ofd_namespace"Content",
  content_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Layer", &content_t::layer_)
  )
)

struct page_t {
  std::optional<st_string> namespace_;
  st_vector<_template_t> templates_;
  st_vector<st_loc> page_res_;
  std::optional<page_area_t> area_;
  std::optional<content_t> content_;
  std::optional<actions_t> actions_;
};

REFLECT_STRUCT(
  ofd_namespace"Page",
  page_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &page_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Template", &page_t::templates_),
    REFLECT_MEMBER(ofd_namespace"PageRes", &page_t::page_res_),
    REFLECT_MEMBER(ofd_namespace"Area", &page_t::area_),
    REFLECT_MEMBER(ofd_namespace"Content", &page_t::content_),
    REFLECT_MEMBER(ofd_namespace"Actions", &page_t::actions_)
  )
)
} // tmpofd
