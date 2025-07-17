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
  DEFINE_VARIANT_ALIAS(clip_area_op_t, std::unique_ptr<path_t>, std::unique_ptr<text_t>),
  DEFINE_VARIANT_TYPE(std::unique_ptr<path_t>, ofd_namespace"Path")
  DEFINE_VARIANT_TYPE(std::unique_ptr<text_t>, ofd_namespace"Text")
)

struct clip_area_t {
  std::optional<st_ref_id> draw_param_;
  std::optional<st_array<st_double> > ctm_;
  clip_area_op_t ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Area",
  clip_area_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("DrawParam", &clip_area_t::draw_param_),
    REFLECT_MEMBER("CTM", &clip_area_t::ctm_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Path", &clip_area_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Text", &clip_area_t::ops_)
  )
)

struct clip_t {
  clip_area_t area_;
};

REFLECT_STRUCT(
  ofd_namespace"Clip",
  clip_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Area", &clip_t::area_)
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

REFLECT_STRUCT(
  ofd_namespace"GraphicUnit",
  graphic_unit_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Boundary", &graphic_unit_t::boundary_),
    REFLECT_MEMBER("Name", &graphic_unit_t::name_),
    REFLECT_MEMBER("Visible", &graphic_unit_t::visible_),
    REFLECT_MEMBER("CTM", &graphic_unit_t::ctm_),
    REFLECT_MEMBER("DrawParam", &graphic_unit_t::draw_param_),
    REFLECT_MEMBER("LineWidth", &graphic_unit_t::line_width_),
    REFLECT_MEMBER("Cap", &graphic_unit_t::cap_),
    REFLECT_MEMBER("Join", &graphic_unit_t::join_),
    REFLECT_MEMBER("MiterLimit", &graphic_unit_t::miter_limit_),
    REFLECT_MEMBER("DashOffset", &graphic_unit_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &graphic_unit_t::dash_pattern_),
    REFLECT_MEMBER("Alpha", &graphic_unit_t::alpha_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &graphic_unit_t::actions_),
    REFLECT_MEMBER(ofd_namespace"Clips", &graphic_unit_t::clips_)
  )
)
} // tmpofd
