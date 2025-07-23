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

#include "tmpofd/core/reflection/reflection.h"

namespace tmpofd {
struct annotation_page_t {
  st_ref_id page_id_;
  st_loc file_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"Page",
  annotation_page_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("PageID", &annotation_page_t::page_id_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"FileLoc", &annotation_page_t::file_loc_)
  )
)

struct annotations_t {
  std::optional<st_string> namespace_;
  st_vector<annotation_page_t> page_;
};

REFLECT_STRUCT(
  ofd_namespace"Annotations",
  annotations_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &annotations_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Page", &annotations_t::page_)
  )
)
} // tmpofd
