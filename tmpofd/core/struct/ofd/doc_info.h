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
struct keywords_t {
  st_vector<st_string> keyword_;
};

REFLECT_STRUCT(
  ofd_namespace"Keywords",
  keywords_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Keyword", &keywords_t::keyword_)
  )
)

struct custom_data_t {
  st_string name_;
  st_string leaf_value;
};

REFLECT_STRUCT(
  ofd_namespace"CustomData",
  custom_data_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Name", &custom_data_t::name_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER("", &custom_data_t::leaf_value)
  )
)

struct custom_datas_t {
  st_vector<custom_data_t> custom_data_;
};

REFLECT_STRUCT(
  ofd_namespace"CustomDatas",
  custom_datas_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"CustomData", &custom_datas_t::custom_data_)
  )
)

struct doc_info_t {
  st_string doc_id_;
  std::optional<st_string> title_;
  std::optional<st_string> author_;
  std::optional<st_string> subject_;
  std::optional<st_string> abstract_;
  std::optional<st_date> creation_date_;
  std::optional<st_date> mod_date_;
  std::optional<st_string> doc_usage_;
  std::optional<st_loc> cover_;
  std::optional<keywords_t> keywords_;
  std::optional<st_string> creator_;
  std::optional<st_string> creator_version_;
  std::optional<custom_datas_t> custom_datas_;
};

REFLECT_STRUCT(
  ofd_namespace"DocInfo",
  doc_info_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"DocID", &doc_info_t::doc_id_),
    REFLECT_MEMBER(ofd_namespace"Title", &doc_info_t::title_),
    REFLECT_MEMBER(ofd_namespace"Author", &doc_info_t::author_),
    REFLECT_MEMBER(ofd_namespace"Subject", &doc_info_t::subject_),
    REFLECT_MEMBER(ofd_namespace"Abstract", &doc_info_t::abstract_),
    REFLECT_MEMBER(ofd_namespace"CreationDate", &doc_info_t::creation_date_),
    REFLECT_MEMBER(ofd_namespace"ModDate", &doc_info_t::mod_date_),
    REFLECT_MEMBER(ofd_namespace"DocUsage", &doc_info_t::doc_usage_),
    REFLECT_MEMBER(ofd_namespace"Cover", &doc_info_t::cover_),
    REFLECT_MEMBER(ofd_namespace"Keywords", &doc_info_t::keywords_),
    REFLECT_MEMBER(ofd_namespace"Creator", &doc_info_t::creator_),
    REFLECT_MEMBER(ofd_namespace"CreatorVersion", &doc_info_t::creator_version_),
    REFLECT_MEMBER(ofd_namespace"CustomDatas", &doc_info_t::custom_datas_)
  )
)
} // tmpofd
