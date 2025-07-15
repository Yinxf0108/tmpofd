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

namespace tmpofd {
template<typename E>
struct enum_converter;

enum class z_order_t { Background, Foreground };
template<>
struct enum_converter<z_order_t> {
  static std::string to_string(const z_order_t e) {
    switch (e) {
      case z_order_t::Background: return "Background";
      case z_order_t::Foreground: return "Foreground";
    }
    return "";
  }
  static std::optional<z_order_t> from_string(const std::string_view s) {
    if (s == "Background") return z_order_t::Background;
    if (s == "Foreground") return z_order_t::Foreground;
    return std::nullopt;
  }
};

// TODO: Move the full specialization converter to the corresponding file

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

enum class signature_type_t { Seal, Sign };
template<>
struct enum_converter<signature_type_t> {
  static std::string to_string(const signature_type_t e) {
    switch (e) {
      case signature_type_t::Seal: return "Seal";
      case signature_type_t::Sign: return "Sign";
    }
    return "";
  }
  static std::optional<signature_type_t> from_string(const std::string_view s) {
    if (s == "Seal") return signature_type_t::Seal;
    if (s == "Sign") return signature_type_t::Sign;
    return std::nullopt;
  }
};

enum class references_check_method_t { MD5, SHA1 };
template<>
struct enum_converter<references_check_method_t> {
  static std::string to_string(const references_check_method_t e) {
    switch (e) {
      case references_check_method_t::MD5: return "MD5";
      case references_check_method_t::SHA1: return "SHA1";
    }
    return "";
  }
  static std::optional<references_check_method_t> from_string(const std::string_view s) {
    if (s == "MD5") return references_check_method_t::MD5;
    if (s == "SHA1") return references_check_method_t::SHA1;
    return std::nullopt;
  }
};

enum class layer_type_t { Body, Background, Foreground, Custom };
template<>
struct enum_converter<layer_type_t> {
  static std::string to_string(const layer_type_t e) {
    switch (e) {
      case layer_type_t::Body: return "Body";
      case layer_type_t::Background: return "Background";
      case layer_type_t::Foreground: return "Foreground";
      case layer_type_t::Custom: return "Custom";
    }
    return "";
  }
  static std::optional<layer_type_t> from_string(const std::string_view s) {
    if (s == "Body") return layer_type_t::Body;
    if (s == "Background") return layer_type_t::Background;
    if (s == "Foreground") return layer_type_t::Foreground;
    if (s == "Custom") return layer_type_t::Custom;
    return std::nullopt;
  }
};

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

enum class weight_t {
  _0 = 0, _100 = 100, _200 = 200, _300 = 300, _400 = 400, _500 = 500,
  _600 = 600, _700 = 700, _800 = 800, _900 = 900, _1000 = 1000
};
template<>
struct enum_converter<weight_t> {
  static std::string to_string(const weight_t e) {
    switch (e) {
      case weight_t::_0: return "0";
      case weight_t::_100: return "100";
      case weight_t::_200: return "200";
      case weight_t::_300: return "300";
      case weight_t::_400: return "400";
      case weight_t::_500: return "500";
      case weight_t::_600: return "600";
      case weight_t::_700: return "700";
      case weight_t::_800: return "800";
      case weight_t::_900: return "900";
      case weight_t::_1000: return "1000";
    }
    return "";
  }
  static std::optional<weight_t> from_string(const std::string_view s) {
    if (s == "0") return weight_t::_0;
    if (s == "100") return weight_t::_100;
    if (s == "200") return weight_t::_200;
    if (s == "300") return weight_t::_300;
    if (s == "400") return weight_t::_400;
    if (s == "500") return weight_t::_500;
    if (s == "600") return weight_t::_600;
    if (s == "700") return weight_t::_700;
    if (s == "800") return weight_t::_800;
    if (s == "900") return weight_t::_900;
    if (s == "1000") return weight_t::_1000;
    return std::nullopt;
  }
};

enum class rule_type_t { NonZero, EvenOdd };
template<>
struct enum_converter<rule_type_t> {
  static std::string to_string(const rule_type_t e) {
    switch (e) {
      case rule_type_t::NonZero: return "NonZero";
      case rule_type_t::EvenOdd: return "Even-Odd";
    }
    return "";
  }
  static std::optional<rule_type_t> from_string(const std::string_view s) {
    if (s == "NonZero") return rule_type_t::NonZero;
    if (s == "Even-Odd") return rule_type_t::EvenOdd;
    return std::nullopt;
  }
};

enum class reflect_method_t { Normal, Row, Column, RowAndColumn };
template<>
struct enum_converter<reflect_method_t> {
  static std::string to_string(const reflect_method_t e) {
    switch (e) {
      case reflect_method_t::Normal: return "Normal";
      case reflect_method_t::Row: return "Row";
      case reflect_method_t::Column: return "Column";
      case reflect_method_t::RowAndColumn: return "RowAndColumn";
    }
    return "";
  }
  static std::optional<reflect_method_t> from_string(const std::string_view s) {
    if (s == "Normal") return reflect_method_t::Normal;
    if (s == "Row") return reflect_method_t::Row;
    if (s == "Column") return reflect_method_t::Column;
    if (s == "RowAndColumn") return reflect_method_t::RowAndColumn;
    return std::nullopt;
  }
};

template<typename E>
struct enum_string_t {
  private:
    st_string value_;

  public:
    enum_string_t() = default;
    explicit enum_string_t(const st_string &s) : value_(s) {}
    explicit enum_string_t(st_string &&s) : value_(std::move(s)) {}
    explicit enum_string_t(const char *s) : value_(s) {}
    explicit enum_string_t(E enum_val) : value_(enum_converter<E>::to_string(enum_val)) {}

    enum_string_t &operator=(const st_string &s) {
      value_ = s;
      return *this;
    }
    enum_string_t &operator=(st_string &&s) {
      value_ = std::move(s);
      return *this;
    }
    enum_string_t &operator=(const char *s) {
      value_ = s;
      return *this;
    }
    enum_string_t &operator=(E enum_val) {
      value_ = enum_converter<E>::to_string(enum_val);
      return *this;
    }

    explicit operator const st_string &() const { return value_; }
    explicit operator st_string &() { return value_; }

    [[nodiscard]] const st_string &str() const { return value_; }

    std::optional<E> to_enum() const {
      return enum_converter<E>::from_string(value_);
    }
};

template<typename E>
bool operator==(const enum_string_t<E> &lhs, E rhs) { return lhs.str() == enum_converter<E>::to_string(rhs); }
template<typename E>
bool operator!=(const enum_string_t<E> &lhs, E rhs) { return !(lhs == rhs); }
template<typename E>
bool operator==(E lhs, const enum_string_t<E> &rhs) { return rhs == lhs; }
template<typename E>
bool operator!=(E lhs, const enum_string_t<E> &rhs) { return !(rhs == lhs); }

template<typename E>
bool operator==(const enum_string_t<E> &lhs, const st_string &rhs) { return lhs.str() == rhs; }
template<typename E>
bool operator!=(const enum_string_t<E> &lhs, const st_string &rhs) { return lhs.str() != rhs; }
template<typename E>
bool operator==(const st_string &lhs, const enum_string_t<E> &rhs) { return lhs == rhs.str(); }
template<typename E>
bool operator!=(const st_string &lhs, const enum_string_t<E> &rhs) { return lhs != rhs.str(); }
} // tmpofd
