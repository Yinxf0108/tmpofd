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

#include "tmpofd/core/struct/ofd/doc_body.h"

namespace tmpofd {
struct ofd_t {
  st_string version_;
  st_string doc_type_;

  st_vector<doc_body_t> doc_bodies_;
};

REFLECT_STRUCT(
  ofd_namespace"OFD",
  ofd_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Version", &ofd_t::version_),
    REFLECT_MEMBER("DocType", &ofd_t::doc_type_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"DocBody", &ofd_t::doc_bodies_)
  )
)
} // tmpofd
