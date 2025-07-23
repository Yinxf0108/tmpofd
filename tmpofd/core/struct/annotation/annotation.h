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

#include "tmpofd/core/struct/page/page_block.h"

namespace tmpofd {
struct parameter_t {
  st_string name_;
  st_string leaf_value;
};

REFLECT_STRUCT(
  ofd_namespace"Parameter",
  parameter_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Name", &parameter_t::name_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER("", &parameter_t::leaf_value)
  )
)

struct parameters_t {
  st_vector<parameter_t> parameter_;
};

REFLECT_STRUCT(
  ofd_namespace"Parameters",
  parameters_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Parameter", &parameters_t::parameter_)
  )
)

struct appearance_t : page_block_t {
  std::optional<st_box<st_double> > boundary_;
};

REFLECT_STRUCT(
  ofd_namespace"Appearance",
  appearance_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Boundary", &appearance_t::boundary_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"TextObject", &appearance_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PathObject", &appearance_t::ops_),
    REFLECT_MEMBER(ofd_namespace"ImageObject", &appearance_t::ops_),
    REFLECT_MEMBER(ofd_namespace"CompositeObject", &appearance_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PageBlock", &appearance_t::ops_)
  )
)

enum class annotation_type_t { Link, Path, Highlight, Stamp, Watermark };
template<>
struct enum_converter<annotation_type_t> {
  static std::string to_string(const annotation_type_t e) {
    switch (e) {
      case annotation_type_t::Link: return "Link";
      case annotation_type_t::Path: return "Path";
      case annotation_type_t::Highlight: return "Highlight";
      case annotation_type_t::Stamp: return "Stamp";
      case annotation_type_t::Watermark: return "Watermark";
    }
    return "";
  }
  static std::optional<annotation_type_t> from_string(const std::string_view s) {
    if (s == "Link") return annotation_type_t::Link;
    if (s == "Path") return annotation_type_t::Path;
    if (s == "Highlight") return annotation_type_t::Highlight;
    if (s == "Stamp") return annotation_type_t::Stamp;
    if (s == "Watermark") return annotation_type_t::Watermark;
    return std::nullopt;
  }
};

struct annot_t {
  st_id id_;
  enum_string_t<annotation_type_t> type_;
  st_string creator_;
  st_date last_mod_date_;
  std::optional<bool> visible_;
  std::optional<st_string> subtype_;
  std::optional<bool> print_;
  std::optional<bool> no_zoom_;
  std::optional<bool> no_rotate_;
  std::optional<bool> read_only_;
  std::optional<st_string> remark_;
  std::optional<parameters_t> parameters_;
  appearance_t appearance_;
};

REFLECT_STRUCT(
  ofd_namespace"Annot",
  annot_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &annot_t::id_),
    REFLECT_MEMBER("Type", &annot_t::type_),
    REFLECT_MEMBER("Creator", &annot_t::creator_),
    REFLECT_MEMBER("LastModDate", &annot_t::last_mod_date_),
    REFLECT_MEMBER("Visible", &annot_t::visible_),
    REFLECT_MEMBER("Subtype", &annot_t::subtype_),
    REFLECT_MEMBER("Print", &annot_t::print_),
    REFLECT_MEMBER("NoZoom", &annot_t::no_zoom_),
    REFLECT_MEMBER("NoRotate", &annot_t::no_rotate_),
    REFLECT_MEMBER("ReadOnly", &annot_t::read_only_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Remark", &annot_t::remark_),
    REFLECT_MEMBER(ofd_namespace"Parameters", &annot_t::parameters_),
    REFLECT_MEMBER(ofd_namespace"Appearance", &annot_t::appearance_)
  )
)

struct page_annot_t {
  std::optional<st_string> namespace_;
  st_vector<annot_t> annot_;
};

REFLECT_STRUCT(
  ofd_namespace"PageAnnot",
  page_annot_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &page_annot_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Annot", &page_annot_t::annot_)
  )
)
} // tmpofd
