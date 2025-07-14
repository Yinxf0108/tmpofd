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

#include "tmpofd/core/struct/common/complex_type.h"

namespace tmpofd {

struct template_page_t {
  st_id id_;
  std::optional<st_string> name_;
  std::optional<enum_string_t<z_order_t> > z_order_;
  st_loc base_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"TemplatePage",
  template_page_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &template_page_t::id_),
    REFLECT_MEMBER("Name", &template_page_t::name_),
    REFLECT_MEMBER("ZOrder", &template_page_t::z_order_),
    REFLECT_MEMBER("BaseLoc", &template_page_t::base_loc_)
  )
  REFLECT_NODE()
)

struct common_data_t {
  st_id max_unit_id_;
  page_area_t page_area_;
  st_vector<st_loc> public_res_;
  st_vector<st_loc> document_res_;
  st_vector<template_page_t> template_page_;
  std::optional<st_ref_id> default_cs_;
};

REFLECT_STRUCT(
  ofd_namespace"CommonData",
  common_data_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"MaxUnitID", &common_data_t::max_unit_id_),
    REFLECT_MEMBER(ofd_namespace"PageArea", &common_data_t::page_area_),
    REFLECT_MEMBER(ofd_namespace"PublicRes", &common_data_t::public_res_),
    REFLECT_MEMBER(ofd_namespace"DocumentRes", &common_data_t::document_res_),
    REFLECT_MEMBER(ofd_namespace"TemplatePage", &common_data_t::template_page_),
    REFLECT_MEMBER(ofd_namespace"DefaultCS", &common_data_t::default_cs_)
  )
)

} // tmpofd
