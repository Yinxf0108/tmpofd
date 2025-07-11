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

#include "tmpofd/core/struct/common/simple_type.h"
#include "tmpofd/core/reflection/reflection.h"

namespace tmpofd {
struct dest_t {
  st_string type_;
  st_ref_id page_id_;
  st_double left_;
  st_double top_;
  st_double right_;
  st_double bottom_;
  st_double zoom_;
};

REFLECT_STRUCT(
  ofd_namespace"Dest",
  dest_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Type", &dest_t::type_),
    REFLECT_MEMBER("PageID", &dest_t::page_id_),
    REFLECT_MEMBER("Left", &dest_t::left_),
    REFLECT_MEMBER("Top", &dest_t::top_),
    REFLECT_MEMBER("Right", &dest_t::right_),
    REFLECT_MEMBER("Bottom", &dest_t::bottom_),
    REFLECT_MEMBER("Zoom", &dest_t::zoom_)
  )
  REFLECT_NODE()
)

struct page_area_t {
  st_box<st_double> physical_box_;
  st_box<st_double> application_box_;
  st_box<st_double> content_box_;
  st_box<st_double> bleed_box_;
};

REFLECT_STRUCT(
  ofd_namespace"PageArea",
  page_area_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"PhysicalBox", &page_area_t::physical_box_),
    REFLECT_MEMBER(ofd_namespace"ApplicationBox", &page_area_t::application_box_),
    REFLECT_MEMBER(ofd_namespace"ContentBox", &page_area_t::content_box_),
    REFLECT_MEMBER(ofd_namespace"BleedBox", &page_area_t::bleed_box_)
  )
)
} // tmpofd
