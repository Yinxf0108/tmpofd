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

#include "tmpofd/core/traits/std_traits.h"

#include <chrono>
#include <filesystem>

namespace tmpofd {
template<typename>
inline constexpr bool always_false_v = false;

using st_bool = bool;

using st_int = int;

template<std::floating_point T>
T to_floating(const std::string &s);

template<>
inline float to_floating<float>(const std::string &s) {
  size_t pos = 0;
  const auto result = std::stof(s, &pos);
  if (pos != s.length()) {
    throw std::invalid_argument("String contains trailing non-numeric characters.");
  }

  return result;
}

template<>
inline double to_floating<double>(const std::string &s) {
  size_t pos = 0;
  const auto result = std::stod(s, &pos);
  if (pos != s.length()) {
    throw std::invalid_argument("String contains trailing non-numeric characters.");
  }

  return result;
}

template<>
inline long double to_floating<long double>(const std::string &s) {
  size_t pos = 0;
  const auto result = std::stold(s, &pos);
  if (pos != s.length()) {
    throw std::invalid_argument("String contains trailing non-numeric characters.");
  }

  return result;
}

template<std::floating_point T = double>
struct floating_t {
  T value_;
  int precision_{};

  void from_string(const std::string_view s) {
    const auto first = s.find_first_not_of(" \t\n\r");
    if (std::string_view::npos == first)
      throw std::runtime_error("Expected number value, but got '" + std::string{s} + "'");

    const auto last = s.find_last_not_of(" \t\n\r");
    const std::string str(s.substr(first, last - first + 1));

    try {
      value_ = to_floating<T>(str);
    } catch (const std::exception &e) {
      throw std::invalid_argument(
        "Failed to convert string to floating-point: \"" + std::string{s} + "\". Reason: " + e.what()
      );
    }

    if (const auto dot_pos = str.find('.'); std::string::npos != dot_pos) {
      if (const auto end_of_digits = str.find_first_not_of("0123456789", dot_pos + 1);
        std::string::npos == end_of_digits
      ) {
        precision_ = static_cast<int>(str.length() - dot_pos - 1);
      } else {
        precision_ = static_cast<int>(end_of_digits - dot_pos - 1);
      }
    } else {
      precision_ = 0;
    }
  }

  explicit floating_t(const T value = 0.0)
    : value_(value), precision_(-1) {}

  explicit floating_t(const std::string_view s) { from_string(s); }
  explicit floating_t(const std::string &s) : floating_t(std::string_view{s}) {}
  explicit floating_t(const char *s) : floating_t(std::string_view{s}) {}

  floating_t &operator=(const T value) {
    value_ = value;
    return *this;
  }

  floating_t &operator=(const std::string_view s) {
    from_string(s);
    return *this;
  }
  floating_t &operator=(const std::string &s) {
    from_string(s);
    return *this;
  }
  floating_t &operator=(const char *s) {
    from_string(s);
    return *this;
  }

  explicit operator T() const { return value_; }
  T value() const { return value_; }

  [[nodiscard]] std::string to_string() const {
    std::ostringstream oss;
    if (precision_ >= 0) {
      oss << std::fixed << std::setprecision(precision_) << value_;
    } else {
      oss << std::setprecision(std::numeric_limits<T>::max_digits10) << value_;
    }
    return oss.str();
  }

  template<typename U> requires std::is_arithmetic_v<std::remove_cvref_t<U> >
  bool operator==(const U &other) const {
    return value_ == static_cast<T>(other);
  }

  template<typename U> requires std::is_arithmetic_v<std::remove_cvref_t<U> >
  auto operator<=>(const U &other) const {
    return value_ <=> static_cast<T>(other);
  }

  bool operator==(const floating_t &) const = default;

  auto operator<=>(const floating_t &) const = default;
};

template<std::floating_point T>
bool operator==(const floating_t<T> &lhs, std::string_view rhs) {
  try {
    return lhs.value() == floating_t<T>(rhs).value();
  } catch (const std::exception &) {
    return false;
  }
}

template<std::floating_point T>
bool operator==(std::string_view lhs, const floating_t<T> &rhs) {
  return rhs == lhs;
}

template<std::floating_point T>
std::istream &operator>>(std::istream &is, floating_t<T> &f) {
  return is >> f.value_;
}

template<std::floating_point T>
std::ostream &operator<<(std::ostream &os, const floating_t<T> &f) {
  return os << f.value_;
}

template<typename T>
concept is_st_int = std::same_as<st_int, std::remove_cvref_t<T> > ;

template<typename>
struct is_floating_t_trait : std::false_type {};

template<std::floating_point T>
struct is_floating_t_trait<floating_t<T> > : std::true_type {};

template<typename T>
concept is_floating_t = is_floating_t_trait<std::remove_cvref_t<T> >::value;

template<typename T>
concept is_st_number = is_st_int<T> || is_floating_t<T>;

using st_double = floating_t<>;

using st_string = std::string;

using st_string_view = std::string_view;

template<typename T, typename Allocator = std::allocator<T> >
using st_vector = std::vector<T, Allocator>;

using st_date = std::chrono::year_month_day;

using st_date_time = std::chrono::system_clock::time_point;

#define ofd_namespace "ofd:"
#define leaf_value leaf_value_

/**
* 包结构内文件的路径，“.”表示当前路径，“..”表示父路径。
* 约定：1.“/”代表根节点；2.未显示指定时代表当前路径；3.路径区分大小写
*/
using st_loc = std::filesystem::path;

/**
* 数组，以空格来分割元素。元素可以是除st_loc、st_array外的数据类型，不可嵌套
*/
template<typename T> requires (!std::same_as<st_loc, std::remove_cvref_t<T> > && !is_vector<T>)
struct st_array;

template<std::unsigned_integral T>
T to_unsigned_int(const std::string &s);

template<>
inline unsigned long to_unsigned_int<unsigned long>(const std::string &s) {
  size_t pos = 0;
  const auto result = std::stoul(s, &pos);
  if (pos != s.length()) {
    throw std::invalid_argument("String contains trailing non-numeric characters.");
  }

  return result;
}

template<>
inline unsigned long long to_unsigned_int<unsigned long long>(const std::string &s) {
  size_t pos = 0;
  const auto result = std::stoull(s, &pos);
  if (pos != s.length()) {
    throw std::invalid_argument("String contains trailing non-numeric characters.");
  }

  return result;
}

template<std::unsigned_integral T = unsigned long long>
struct unsigned_int_t {
  T value_;

  void from_string(const std::string_view s) {
    const auto first = s.find_first_not_of(" \t\n\r");
    if (std::string_view::npos == first)
      throw std::runtime_error("Expected number value, but got '" + std::string{s} + "'");

    const auto last = s.find_last_not_of(" \t\n\r");
    const std::string str(s.substr(first, last - first + 1));

    try {
      value_ = to_unsigned_int<T>(str);
    } catch (const std::exception &e) {
      throw std::invalid_argument(
        "Failed to convert string to floating-point: \"" + std::string{s} + "\". Reason: " + e.what()
      );
    }
  }

  unsigned_int_t() = default;

  explicit unsigned_int_t(const T value) : value_(value) {}

  explicit unsigned_int_t(const int value) : value_(value) {}

  explicit unsigned_int_t(const std::string_view s) { from_string(s); }
  explicit unsigned_int_t(const std::string &s) : unsigned_int_t(std::string_view{s}) {}
  explicit unsigned_int_t(const char *s) : unsigned_int_t(std::string_view{s}) {}

  unsigned_int_t &operator=(const T value) {
    value_ = value;
    return *this;
  }

  unsigned_int_t &operator=(const std::string_view s) {
    from_string(s);
    return *this;
  }
  unsigned_int_t &operator=(const std::string &s) {
    from_string(s);
    return *this;
  }
  unsigned_int_t &operator=(const char *s) {
    from_string(s);
    return *this;
  }

  explicit operator T() const { return value_; }
  T value() const { return value_; }

  [[nodiscard]] std::string to_string() const {
    std::ostringstream oss;
    oss << value_;
    return oss.str();
  }

  template<typename U> requires std::is_arithmetic_v<std::remove_cvref_t<U> >
  bool operator==(const U &other) const {
    return value_ == static_cast<T>(other);
  }

  template<typename U> requires std::is_arithmetic_v<std::remove_cvref_t<U> >
  auto operator<=>(const U &other) const {
    return value_ <=> static_cast<T>(other);
  }

  auto operator<=>(const unsigned_int_t &) const = default;
};

template<std::unsigned_integral T>
bool operator==(const unsigned_int_t<T> &lhs, std::string_view rhs) {
  try {
    return lhs.value() == unsigned_int_t<T>(rhs).value();
  } catch (const std::exception &) {
    return false;
  }
}

template<std::unsigned_integral T>
bool operator==(std::string_view lhs, const unsigned_int_t<T> &rhs) {
  return rhs == lhs;
}

template<std::unsigned_integral T>
std::istream &operator>>(std::istream &is, unsigned_int_t<T> &f) {
  return is >> f.value_;
}

template<std::unsigned_integral T>
std::ostream &operator<<(std::ostream &os, const unsigned_int_t<T> &f) {
  return os << f.value_;
}

/**
* 标识，无符号整数，应在文档内唯一。0表示无效标识
*/
using st_id = unsigned_int_t<>;

/**
* 标识引用，无符号整数，此标识应为文档内已定义的标识
*/
using st_ref_id = st_id;

/**
* 点坐标，以空格分割，前者为x值，后者为y值，可以是整数或者浮点数
*/
template<is_st_number T>
struct st_pos;

/**
* 矩形区域，以空格分割，前两个值代表了该矩形的左上角的坐标，后两个值依次表示该矩形的宽和高，可以是整数或者浮点数，后两个值应大于0
*/
template<is_st_number T>
struct st_box;
} // tmpofd
