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
  st_id id_;
};

struct _path_t : path_t {
  st_id id_;
};

struct _image_t : image_t {
  st_id id_;
};

struct _composite_t : composite_t {
  st_id id_;
};

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(page_block_op_t, _text_t, _path_t, _image_t, _composite_t, std:: unique_ptr<page_block_t >),
  DEFINE_VARIANT_TYPE(_text_t, ofd_namespace"TextObject")
  DEFINE_VARIANT_TYPE(_path_t, ofd_namespace"PathObject")
  DEFINE_VARIANT_TYPE(_image_t, ofd_namespace"ImageObject")
  DEFINE_VARIANT_TYPE(_composite_t, ofd_namespace"CompositeObject")
  DEFINE_VARIANT_TYPE(std::unique_ptr<page_block_t>, ofd_namespace"PageBlock")
)

struct page_block_t {
  st_vector<page_block_op_t> ops_;
};

REFLECT_STRUCT(
  ofd_namespace"PageBlock",
  page_block_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"TextObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PathObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"ImageObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"CompositeObject", &page_block_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PageBlock", &page_block_t::ops_)
  )
)
} // tmpofd
