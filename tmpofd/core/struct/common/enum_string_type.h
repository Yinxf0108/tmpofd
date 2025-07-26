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

enum class map_type_t { Direct, Repeat, Reflect };
template<>
struct enum_converter<map_type_t> {
  static std::string to_string(const map_type_t e) {
    switch (e) {
      case map_type_t::Direct: return "Direct";
      case map_type_t::Repeat: return "Repeat";
      case map_type_t::Reflect: return "Reflect";
    }
    return "";
  }
  static std::optional<map_type_t> from_string(const std::string_view s) {
    if (s == "Direct") return map_type_t::Direct;
    if (s == "Repeat") return map_type_t::Repeat;
    if (s == "Reflect") return map_type_t::Reflect;
    return std::nullopt;
  }
};

enum class extend_t { Extend0, Extend1, Extend2, Extend3 };
template<>
struct enum_converter<extend_t> {
  static std::string to_string(const extend_t e) {
    switch (e) {
      case extend_t::Extend0: return "0";
      case extend_t::Extend1: return "1";
      case extend_t::Extend2: return "2";
      case extend_t::Extend3: return "3";
    }
    return "";
  }
  static std::optional<extend_t> from_string(const std::string_view s) {
    if (s == "0") return extend_t::Extend0;
    if (s == "1") return extend_t::Extend1;
    if (s == "2") return extend_t::Extend2;
    if (s == "3") return extend_t::Extend3;
    return std::nullopt;
  }
};

template<typename E>
struct enum_string_t {
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

  private:
    st_string value_;
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
