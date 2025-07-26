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
struct _page_t {
  st_id id_;
  st_loc base_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"Page",
  _page_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &_page_t::id_),
    REFLECT_MEMBER("BaseLoc", &_page_t::base_loc_)
  )
  REFLECT_NODE()
)

struct pages_t {
  st_vector<_page_t> page_;

  using const_iterator = st_vector<_page_t>::const_iterator;
  using iterator = st_vector<_page_t>::iterator;

  [[nodiscard]] const_iterator begin() const { return page_.begin(); }
  [[nodiscard]] const_iterator end() const { return page_.end(); }
  iterator begin() { return page_.begin(); }
  iterator end() { return page_.end(); }

  [[nodiscard]] bool empty() const { return page_.empty(); }
  [[nodiscard]] size_t size() const { return page_.size(); }

  _page_t &operator[](const size_t index) { return page_[index]; }
  const _page_t &operator[](const size_t index) const { return page_[index]; }
};

REFLECT_STRUCT(
  ofd_namespace"Pages",
  pages_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Page", &pages_t::page_)
  )
)
} // tmpofd
