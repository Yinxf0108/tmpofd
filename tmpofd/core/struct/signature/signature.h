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
struct provider_t {
  st_string provider_name_;
  std::optional<st_string> version_;
  std::optional<st_string> company_;
};

REFLECT_STRUCT(
  ofd_namespace"Provider",
  provider_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ProviderName", &provider_t::provider_name_),
    REFLECT_MEMBER("Version", &provider_t::version_),
    REFLECT_MEMBER("Company", &provider_t::company_)
  )
  REFLECT_NODE()
)

struct check_value_t {
  st_string leaf_value;
};

REFLECT_STRUCT(
  ofd_namespace"CheckValue",
  check_value_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER("", &check_value_t::leaf_value)
  )
)

struct reference_t {
  st_loc file_ref_;
  check_value_t check_value_;
};

REFLECT_STRUCT(
  ofd_namespace"Reference",
  reference_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("FileRef", &reference_t::file_ref_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"CheckValue", &reference_t::check_value_)
  )
)

enum class references_check_method_t { MD5, SHA1, SM3 };
template<>
struct enum_converter<references_check_method_t> {
  static std::string to_string(const references_check_method_t e) {
    switch (e) {
      case references_check_method_t::MD5: return "MD5";
      case references_check_method_t::SHA1: return "SHA1";
      case references_check_method_t::SM3: return "SM3";
    }
    return "";
  }
  static std::optional<references_check_method_t> from_string(const std::string_view s) {
    if (s == "MD5") return references_check_method_t::MD5;
    if (s == "SHA1") return references_check_method_t::SHA1;
    if (s == "SM3") return references_check_method_t::SM3;
    return std::nullopt;
  }
};

struct references_t {
  std::optional<enum_string_t<references_check_method_t> > check_method_;
  st_vector<reference_t> reference_;
};

REFLECT_STRUCT(
  ofd_namespace"References",
  references_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("CheckMethod", &references_t::check_method_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Reference", &references_t::reference_)
  )
)

struct stamp_annot_t {
  st_id id_;
  st_ref_id page_ref_;
  st_box<st_double> boundary_;
  std::optional<st_box<st_double>> clip_;
};

REFLECT_STRUCT(
  ofd_namespace"StampAnnot",
  stamp_annot_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &stamp_annot_t::id_),
    REFLECT_MEMBER("PageRef", &stamp_annot_t::page_ref_),
    REFLECT_MEMBER("Boundary", &stamp_annot_t::boundary_),
    REFLECT_MEMBER("Clip", &stamp_annot_t::clip_)
  )
  REFLECT_NODE()
)

struct seal_t {
  st_loc base_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"Seal",
  seal_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"BaseLoc", &seal_t::base_loc_)
  )
)

struct signed_info_t {
  provider_t provider_;
  std::optional<st_string> signature_method_;
  std::optional<st_string> signature_date_time_;
  references_t references_;
  st_vector<stamp_annot_t> stamp_annot_;
  std::optional<seal_t> seal_;
};

REFLECT_STRUCT(
  ofd_namespace"SignedInfo",
  signed_info_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Provider", &signed_info_t::provider_),
    REFLECT_MEMBER(ofd_namespace"SignatureMethod", &signed_info_t::signature_method_),
    REFLECT_MEMBER(ofd_namespace"SignatureDateTime", &signed_info_t::signature_date_time_),
    REFLECT_MEMBER(ofd_namespace"References", &signed_info_t::references_),
    REFLECT_MEMBER(ofd_namespace"StampAnnot", &signed_info_t::stamp_annot_),
    REFLECT_MEMBER(ofd_namespace"Seal", &signed_info_t::seal_)
  )
)

struct signature_t {
  std::optional<st_string> namespace_;
  signed_info_t signed_info_;
  st_loc signed_value_;
};

REFLECT_STRUCT(
  ofd_namespace"Signature",
  signature_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &signature_t::namespace_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"SignedInfo", &signature_t::signed_info_),
    REFLECT_MEMBER(ofd_namespace"SignedValue", &signature_t::signed_value_)
  )
)
} // tmpofd
