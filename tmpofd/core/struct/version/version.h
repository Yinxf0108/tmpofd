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
struct file_t {
  st_id id_;
  st_loc leaf_value;
};

REFLECT_STRUCT(
  ofd_namespace"File",
  file_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &file_t::id_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER("", &file_t::leaf_value)
  )
)

struct file_list_t {
  st_vector<file_t> file_;
};

REFLECT_STRUCT(
  ofd_namespace"FileList",
  file_list_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"File", &file_list_t::file_)
  )
)

struct doc_version_t {
  std::optional<st_string> namespace_;
  st_id id_;
  std::optional<st_string> version_;
  std::optional<st_string> name_;
  std::optional<st_date> creation_date_;
  file_list_t file_list_;
  st_loc doc_root_;
};

REFLECT_STRUCT(
  ofd_namespace"DocVersion",
  doc_version_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &doc_version_t::namespace_),
    REFLECT_MEMBER("ID", &doc_version_t::id_),
    REFLECT_MEMBER("Version", &doc_version_t::version_),
    REFLECT_MEMBER("Name", &doc_version_t::name_),
    REFLECT_MEMBER("CreationDate", &doc_version_t::creation_date_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"FileList", &doc_version_t::file_list_),
    REFLECT_MEMBER(ofd_namespace"DocRoot", &doc_version_t::doc_root_)
  )
)
} // tmpofd
