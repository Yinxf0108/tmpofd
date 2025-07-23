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
struct custom_tag_t {
  st_string namespace_;
  std::optional<st_loc> schema_loc_;
  st_loc file_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"CustomTag",
  custom_tag_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("NameSpace", &custom_tag_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"SchemaLoc", &custom_tag_t::schema_loc_),
    REFLECT_MEMBER(ofd_namespace"FileLoc", &custom_tag_t::file_loc_)
  )
)

struct custom_tags_t {
  std::optional<st_string> namespace_;
  st_vector<custom_tag_t> custom_tag_;
};

REFLECT_STRUCT(
  ofd_namespace"CustomTags",
  custom_tags_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &custom_tags_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"CustomTag", &custom_tags_t::custom_tag_)
  )
)
} // tmpofd
