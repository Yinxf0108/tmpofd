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
#include "tmpofd/core/struct/common/enum_string_type.h"
#include "tmpofd/core/struct/page/color.h"

namespace tmpofd {
struct palette_t {
  st_vector<st_array<st_double> > cv_;
};

REFLECT_STRUCT(
  ofd_namespace"Palette",
  palette_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"CV", &palette_t::cv_)
  )
)

enum class color_space_type_t { GRAY, RGB, CMYK };
template<>
struct enum_converter<color_space_type_t> {
  static std::string to_string(const color_space_type_t e) {
    switch (e) {
      case color_space_type_t::GRAY: return "GRAY";
      case color_space_type_t::RGB: return "RGB";
      case color_space_type_t::CMYK: return "CMYK";
    }
    return "";
  }
  static std::optional<color_space_type_t> from_string(const std::string_view s) {
    if (s == "GRAY") return color_space_type_t::GRAY;
    if (s == "RGB") return color_space_type_t::RGB;
    if (s == "CMYK") return color_space_type_t::CMYK;
    return std::nullopt;
  }
};

struct color_space_t {
  st_id id_{};
  enum_string_t<color_space_type_t> type_;
  std::optional<st_int> bits_per_component_;
  std::optional<st_loc> profile_;
  std::optional<palette_t> palette_;
};

REFLECT_STRUCT(
  ofd_namespace"ColorSpace",
  color_space_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &color_space_t::id_),
    REFLECT_MEMBER("Type", &color_space_t::type_),
    REFLECT_MEMBER("BitsPerComponent", &color_space_t::bits_per_component_),
    REFLECT_MEMBER("Profile", &color_space_t::profile_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Palette", &color_space_t::palette_)
  )
)

struct color_spaces_t {
  st_vector<color_space_t> color_space_;
};

REFLECT_STRUCT(
  ofd_namespace"ColorSpaces",
  color_spaces_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"ColorSpace", &color_spaces_t::color_space_)
  )
)

struct draw_param_t {
  st_id id_;
  std::optional<st_ref_id> relative_;
  std::optional<st_double> line_width_;
  std::optional<st_string> join_;
  std::optional<st_string> cap_;
  std::optional<st_double> dash_offset_;
  std::optional<st_array<st_double> > dash_pattern_;
  std::optional<st_double> miter_limit_;
  std::optional<color_t> fill_color_;
  std::optional<color_t> stroke_color_;
};

REFLECT_STRUCT(
  ofd_namespace"DrawParam",
  draw_param_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &draw_param_t::id_),
    REFLECT_MEMBER("Relative", &draw_param_t::relative_),
    REFLECT_MEMBER("LineWidth", &draw_param_t::line_width_),
    REFLECT_MEMBER("Join", &draw_param_t::join_),
    REFLECT_MEMBER("Cap", &draw_param_t::cap_),
    REFLECT_MEMBER("DashOffset", &draw_param_t::dash_offset_),
    REFLECT_MEMBER("DashPattern", &draw_param_t::dash_pattern_),
    REFLECT_MEMBER("MiterLimit", &draw_param_t::miter_limit_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"FillColor", &draw_param_t::fill_color_),
    REFLECT_MEMBER(ofd_namespace"StrokeColor", &draw_param_t::stroke_color_)
  )
)

struct draw_params_t {
  st_vector<draw_param_t> draw_param_;
};

REFLECT_STRUCT(
  ofd_namespace"DrawParams",
  draw_params_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"DrawParam", &draw_params_t::draw_param_)
  )
)

enum class charset_t { symbol, prc, big5, shift_jis, wansung, johab, unicode };
template<>
struct enum_converter<charset_t> {
  static std::string to_string(const charset_t e) {
    switch (e) {
      case charset_t::symbol: return "symbol";
      case charset_t::prc: return "prc";
      case charset_t::big5: return "big5";
      case charset_t::shift_jis: return "shift-jis";
      case charset_t::wansung: return "wansung";
      case charset_t::johab: return "johab";
      case charset_t::unicode: return "unicode";
    }
    return "";
  }
  static std::optional<charset_t> from_string(const std::string_view s) {
    if (s == "symbol") return charset_t::symbol;
    if (s == "prc") return charset_t::prc;
    if (s == "big5") return charset_t::big5;
    if (s == "shift-jis") return charset_t::shift_jis;
    if (s == "wansung") return charset_t::wansung;
    if (s == "johab") return charset_t::johab;
    if (s == "unicode") return charset_t::unicode;
    return std::nullopt;
  }
};

struct font_t {
  st_id id_;
  st_string font_name_;
  std::optional<st_string> family_name_;
  std::optional<enum_string_t<charset_t> > charset_;
  std::optional<st_bool> italic_;
  std::optional<st_bool> bold_;
  std::optional<st_bool> serif_;
  std::optional<st_bool> fixed_width_;
  std::optional<st_loc> font_file_;
};

REFLECT_STRUCT(
  ofd_namespace"Font",
  font_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &font_t::id_),
    REFLECT_MEMBER("FontName", &font_t::font_name_),
    REFLECT_MEMBER("FamilyName", &font_t::family_name_),
    REFLECT_MEMBER("Charset", &font_t::charset_),
    REFLECT_MEMBER("Italic", &font_t::italic_),
    REFLECT_MEMBER("Bold", &font_t::bold_),
    REFLECT_MEMBER("Serif", &font_t::serif_),
    REFLECT_MEMBER("FixedWidth", &font_t::fixed_width_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"FontFile", &font_t::font_file_)
  )
)

struct fonts_t {
  st_vector<font_t> font_;
};

REFLECT_STRUCT(
  ofd_namespace"Fonts",
  fonts_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Font", &fonts_t::font_)
  )
)

enum class multimedia_type_t { Image, Audio, Video };
template<>
struct enum_converter<multimedia_type_t> {
  static std::string to_string(const multimedia_type_t e) {
    switch (e) {
      case multimedia_type_t::Image: return "Image";
      case multimedia_type_t::Audio: return "Audio";
      case multimedia_type_t::Video: return "Video";
    }
    return "";
  }
  static std::optional<multimedia_type_t> from_string(const std::string_view s) {
    if (s == "Image") return multimedia_type_t::Image;
    if (s == "Audio") return multimedia_type_t::Audio;
    if (s == "Video") return multimedia_type_t::Video;
    return std::nullopt;
  }
};

struct multi_media_t {
  st_id id_;
  enum_string_t<multimedia_type_t> type_;
  std::optional<st_string> format_;
  st_loc media_file_;
};

REFLECT_STRUCT(
  ofd_namespace"MultiMedia",
  multi_media_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &multi_media_t::id_),
    REFLECT_MEMBER("Type", &multi_media_t::type_),
    REFLECT_MEMBER("Format", &multi_media_t::format_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"MediaFile", &multi_media_t::media_file_)
  )
)

struct multi_medias_t {
  st_vector<multi_media_t> multi_media_;
};

REFLECT_STRUCT(
  ofd_namespace"MultiMedias",
  multi_medias_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"MultiMedia", &multi_medias_t::multi_media_)
  )
)

struct _content_t {
  page_block_op_t ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Content",
  _content_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"TextObject", &_content_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PathObject", &_content_t::ops_),
    REFLECT_MEMBER(ofd_namespace"ImageObject", &_content_t::ops_),
    REFLECT_MEMBER(ofd_namespace"CompositeObject", &_content_t::ops_),
    REFLECT_MEMBER(ofd_namespace"PageBlock", &_content_t::ops_)
  )
)

struct composite_graphic_unit_t {
  st_id id_{};
  st_double width_;
  st_double height_;
  std::optional<st_ref_id> thumbnail_;
  std::optional<st_ref_id> substitution_;
  _content_t content_;
};

REFLECT_STRUCT(
  ofd_namespace"CompositeGraphicUnit",
  composite_graphic_unit_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &composite_graphic_unit_t::id_),
    REFLECT_MEMBER("Width", &composite_graphic_unit_t::width_),
    REFLECT_MEMBER("Height", &composite_graphic_unit_t::height_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Thumbnail", &composite_graphic_unit_t::thumbnail_),
    REFLECT_MEMBER(ofd_namespace"Substitution", &composite_graphic_unit_t::substitution_),
    REFLECT_MEMBER(ofd_namespace"Content", &composite_graphic_unit_t::content_)
  )
)

struct composite_graphic_units_t {
  st_vector<composite_graphic_unit_t> composite_graphic_unit_;
};

REFLECT_STRUCT(
  ofd_namespace"CompositeGraphicUnits",
  composite_graphic_units_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"CompositeGraphicUnit", &composite_graphic_units_t::composite_graphic_unit_)
  )
)

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(res_op_t, color_spaces_t, draw_params_t, fonts_t, multi_medias_t, composite_graphic_units_t),
  DEFINE_VARIANT_TYPE(color_spaces_t, ofd_namespace"ColorSpaces")
  DEFINE_VARIANT_TYPE(draw_params_t, ofd_namespace"DrawParams")
  DEFINE_VARIANT_TYPE(fonts_t, ofd_namespace"Fonts")
  DEFINE_VARIANT_TYPE(multi_medias_t, ofd_namespace"MultiMedias")
  DEFINE_VARIANT_TYPE(composite_graphic_units_t, ofd_namespace"CompositeGraphicUnits")
)

struct res_t {
  std::optional<st_string> namespace_;
  st_loc base_loc_;
  st_vector<res_op_t> ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Res",
  res_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("xmlns:ofd", &res_t::namespace_),
    REFLECT_MEMBER("BaseLoc", &res_t::base_loc_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"ColorSpaces", &res_t::ops_),
    REFLECT_MEMBER(ofd_namespace"DrawParams", &res_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Fonts", &res_t::ops_),
    REFLECT_MEMBER(ofd_namespace"MultiMedias", &res_t::ops_),
    REFLECT_MEMBER(ofd_namespace"CompositeGraphicUnits", &res_t::ops_)
  )
)
} // tmpofd
