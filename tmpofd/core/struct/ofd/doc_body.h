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

#include "tmpofd/core/struct/ofd/doc_info.h"
#include "tmpofd/core/struct/ofd/version.h"

namespace tmpofd {
struct versions_t {
  st_vector<version_t> version_;
};

REFLECT_STRUCT(
  ofd_namespace"Versions",
  versions_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Version", &versions_t::version_)
  )
)

struct doc_body_t {
  doc_info_t doc_info_;
  st_loc doc_root_;
  std::optional<versions_t> versions_;
  std::optional<st_loc> signatures_;
};

REFLECT_STRUCT(
  ofd_namespace"DocBody",
  doc_body_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"DocInfo", &doc_body_t::doc_info_),
    REFLECT_MEMBER(ofd_namespace"DocRoot", &doc_body_t::doc_root_),
    REFLECT_MEMBER(ofd_namespace"Versions", &doc_body_t::versions_),
    REFLECT_MEMBER(ofd_namespace"Signatures", &doc_body_t::signatures_)
  )
)
} // tmpofd
