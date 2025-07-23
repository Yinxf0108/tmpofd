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
struct attachment_t {
  st_string id_;
  st_string name_;
  std::optional<st_string> format_;
  std::optional<st_date_time> creation_date_;
  std::optional<st_date_time> mod_date_;
  std::optional<st_double> size_;
  std::optional<bool> visible_;
  std::optional<st_string> usage_;
  std::optional<st_loc> file_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"Attachment",
  attachment_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &attachment_t::id_),
    REFLECT_MEMBER("Name", &attachment_t::name_),
    REFLECT_MEMBER("Format", &attachment_t::format_),
    REFLECT_MEMBER("CreationDate", &attachment_t::creation_date_),
    REFLECT_MEMBER("ModDate", &attachment_t::mod_date_),
    REFLECT_MEMBER("Size", &attachment_t::size_),
    REFLECT_MEMBER("Visible", &attachment_t::visible_),
    REFLECT_MEMBER("Usage", &attachment_t::usage_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"FileLoc", &attachment_t::file_loc_)
  )
)
struct attachments_t {
  std::optional<st_string> namespace_;
  st_vector<attachment_t> attachment_;
};

REFLECT_STRUCT(
  ofd_namespace"Attachments",
  attachments_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &attachments_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Attachment", &attachments_t::attachment_)
  )
)
} // tmpofd
