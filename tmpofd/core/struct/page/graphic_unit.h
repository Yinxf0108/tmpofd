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
struct text_t;
struct path_t;

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(clip_op_t, path_t, text_t),
  DEFINE_VARIANT_TYPE(path_t, ofd_namespace"Path")
  DEFINE_VARIANT_TYPE(text_t, ofd_namespace"Text")
)

struct clip_t {
  std::optional<st_ref_id> draw_param_;
  std::optional<st_array<st_double> > ctm_;
  clip_op_t ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Clip",
  clip_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &clip_t::draw_param_),
    REFLECT_MEMBER("Type", &clip_t::ctm_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Path", &clip_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Text", &clip_t::ops_)
  )
)

struct clips_t {
  st_vector<clip_t> clip_;
};

REFLECT_STRUCT(
  ofd_namespace"Clips",
  clips_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Clip", &clips_t::clip_)
  )
)

enum class cap_type_t { Butt, Round, Square };
template<>
struct enum_converter<cap_type_t> {
  static std::string to_string(const cap_type_t e) {
    switch (e) {
      case cap_type_t::Butt: return "Butt";
      case cap_type_t::Round: return "Round";
      case cap_type_t::Square: return "Square";
    }
    return "";
  }
  static std::optional<cap_type_t> from_string(const std::string_view s) {
    if (s == "Butt") return cap_type_t::Butt;
    if (s == "Round") return cap_type_t::Round;
    if (s == "Square") return cap_type_t::Square;
    return std::nullopt;
  }
};

enum class join_type_t { Miter, Round, Bevel };
template<>
struct enum_converter<join_type_t> {
  static std::string to_string(const join_type_t e) {
    switch (e) {
      case join_type_t::Miter: return "Miter";
      case join_type_t::Round: return "Round";
      case join_type_t::Bevel: return "Bevel";
    }
    return "";
  }
  static std::optional<join_type_t> from_string(const std::string_view s) {
    if (s == "Miter") return join_type_t::Miter;
    if (s == "Round") return join_type_t::Round;
    if (s == "Bevel") return join_type_t::Bevel;
    return std::nullopt;
  }
};

struct graphic_unit_t {
  st_box<st_double> boundary_;
  std::optional<st_string> name_;
  std::optional<st_bool> visible_;
  std::optional<st_array<st_double> > ctm_;
  std::optional<st_ref_id> draw_param_;
  std::optional<st_double> line_width_;
  std::optional<enum_string_t<cap_type_t> > cap_;
  std::optional<enum_string_t<join_type_t> > join_;
  std::optional<st_double> miter_limit_;
  std::optional<st_double> dash_offset_;
  std::optional<st_array<st_double> > dash_pattern_;
  std::optional<st_int> alpha_;
  std::optional<actions_t> actions_;
  std::optional<clips_t> clips_;
};
} // tmpofd
