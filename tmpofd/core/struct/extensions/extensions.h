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
#include "tmpofd/core/struct/common/variant_type.h"

namespace tmpofd {
struct property_t {
  st_string name_;
  std::optional<st_string> type_;
  st_string leaf_value;
};

REFLECT_STRUCT(
  ofd_namespace"Property",
  property_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Name", &property_t::name_),
    REFLECT_MEMBER("Type", &property_t::type_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER("", &property_t::leaf_value)
  )
)

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(extension_content_t, property_t, st_string, st_loc),
  DEFINE_VARIANT_TYPE(property_t, ofd_namespace"Property")
  DEFINE_VARIANT_TYPE(st_string, ofd_namespace"Data")
  DEFINE_VARIANT_TYPE(st_loc, ofd_namespace"ExtendData")
)

struct extension_t {
  st_string app_name_;
  std::optional<st_string> company_;
  std::optional<st_string> app_version_;
  std::optional<st_date_time> date_;
  st_ref_id ref_id_;
  st_vector<extension_content_t> content_;
};

REFLECT_STRUCT(
  ofd_namespace"Extension",
  extension_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("AppName", &extension_t::app_name_),
    REFLECT_MEMBER("Company", &extension_t::company_),
    REFLECT_MEMBER("AppVersion", &extension_t::app_version_),
    REFLECT_MEMBER("Date", &extension_t::date_),
    REFLECT_MEMBER("RefId", &extension_t::ref_id_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Property", &extension_t::content_),
    REFLECT_MEMBER(ofd_namespace"Data", &extension_t::content_),
    REFLECT_MEMBER(ofd_namespace"ExtendData", &extension_t::content_)
  )
)

struct extensions_t {
  std::optional<st_string> namespace_;
  st_vector<extension_t> extension_;
};

REFLECT_STRUCT(
  ofd_namespace"Extensions",
  extensions_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &extensions_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Extension", &extensions_t::extension_)
  )
)
} // tmpofd
