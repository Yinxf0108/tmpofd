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

#include "tmpofd/core/traits/simple_type.h"

#include <cassert>

namespace tmpofd {
/**
* 数组，以空格来分割元素。元素可以是除st_loc、st_array外的数据类型，不可嵌套
*/
template<typename T> requires (!std::same_as<st_loc, remove_opt_t<std::remove_cvref_t<T> > > && !is_vector<T>)
struct st_array {
  private:
    std::vector<T> data_;

  public:
    using value_type = typename std::vector<T>::value_type;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    st_array() = default;
    st_array(std::initializer_list<T> init) : data_(init) {}

    void from_string(const std::string_view str, const char sep = ' ') {
      data_.clear();

      std::string s(str);
      if (' ' != sep) {
        for (char &ch : s) {
          if (sep == ch) {
            ch = ' ';
          }
        }
      }

      std::stringstream ss(s);
      value_type value;
      while (ss >> value) {
        data_.push_back(std::move(value));
      }
    }

    [[nodiscard]] std::string to_string(const char sep = ' ') const {
      if (data_.empty())
        return "";

      std::stringstream ss;
      for (size_t i = 0; i < data_.size(); ++i) {
        ss << data_[i];
        if (i < data_.size() - 1) {
          ss << sep;
        }
      }
      return ss.str();
    }

    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }

    auto size() const { return data_.size(); }
    auto empty() const { return data_.empty(); }

    auto &operator[](size_t index) { return data_[index]; }
    const auto &operator[](size_t index) const { return data_[index]; }

    void push_back(const T &value) { data_.push_back(value); }
    void push_back(T &&value) { data_.push_back(std::move(value)); }

    template<typename... Args>
    void emplace_back(Args &&... args) {
      data_.emplace_back(std::forward<Args>(args)...);
    }
};

/**
* 标识，无符号整数，应在文档内唯一。0表示无效标识
*/
struct st_id {
  std::uint64_t value_;

  constexpr st_id() : value_(0) {}
  constexpr explicit st_id(const std::uint64_t value) : value_(value) {}

  constexpr st_id &operator=(const std::uint64_t value) {
    value_ = value;
    return *this;
  }

  explicit operator const std::uint64_t &() const { return value_; }
  explicit operator std::uint64_t &() { return value_; }

  [[nodiscard]] const std::uint64_t &value() const { return value_; }

  auto operator<=>(const st_id &) const = default;
};

inline std::istream &operator>>(std::istream &is, st_id &id) {
  return is >> id.value_;
}
inline std::ostream &operator<<(std::ostream &os, const st_id &id) {
  return os << id.value_;
}

/**
* 标识引用，无符号整数，此标识应为文档内已定义的标识
*/
struct st_ref_id {
  std::uint64_t value_;

  constexpr st_ref_id() : value_(0) {}
  constexpr explicit st_ref_id(const std::uint64_t v) : value_(v) {}
  constexpr explicit st_ref_id(const st_id &id) : value_(id.value_) {}

  constexpr st_ref_id &operator=(const std::uint64_t value) {
    value_ = value;
    return *this;
  }

  explicit operator const std::uint64_t &() const { return value_; }
  explicit operator std::uint64_t &() { return value_; }

  [[nodiscard]] const std::uint64_t &value() const { return value_; }

  auto operator<=>(const st_ref_id &) const = default;
};

inline std::istream &operator>>(std::istream &is, st_ref_id &id) {
  return is >> id.value_;
}
inline std::ostream &operator<<(std::ostream &os, const st_ref_id &id) {
  return os << id.value_;
}

/**
* 点坐标，以空格分割，前者为x值，后者为y值，可以是整数或者浮点数
*/
template<is_number T>
struct st_pos {
  T x_;
  T y_;

  constexpr st_pos() : x_(T{}), y_(T{}) {}
  constexpr st_pos(T x, T y) : x_(x), y_(y) {}

  void from_string(const std::string_view str, const char sep = ' ') {
    std::string s(str);
    if (' ' != sep) {
      for (char &ch : s) {
        if (sep == ch) {
          ch = ' ';
        }
      }
    }

    std::stringstream ss(s);
    ss >> x_ >> y_;
  }

  [[nodiscard]] std::string to_string(char sep = ' ') const {
    std::stringstream ss;
    ss << x_ << sep << y_;
    return ss.str();
  }

  auto operator<=>(const st_pos &) const = default;
};

/**
* 矩形区域，以空格分割，前两个值代表了该矩形的左上角的坐标，后两个值依次表示该矩形的宽和高，可以是整数或者浮点数，后两个值应大于0
*/
template<is_number T>
struct st_box {
  T x_;
  T y_;
  T width_;
  T height_;

  constexpr st_box() : x_(T{}), y_(T{}), width_(T{}), height_(T{}) {}

  constexpr st_box(T x, T y, T width, T height)
    : x_(x), y_(y), width_(width), height_(height) {
    assert(width_ > T{0} && height_ > T{0} && "st_box: width and height must be positive.");
  }

  void from_string(const std::string_view str, const char sep = ' ') {
    std::string s(str);
    if (' ' != sep) {
      for (char &ch : s) {
        if (sep == ch) {
          ch = ' ';
        }
      }
    }

    std::stringstream ss(s);
    ss >> x_ >> y_ >> width_ >> height_;
    assert(width_ > T{0} && height_ > T{0} && "st_box: width and height must be positive.");
  }

  [[nodiscard]] std::string to_string(char sep = ' ') const {
    std::stringstream ss;
    ss << x_ << sep << y_ << sep << width_ << sep << height_;
    return ss.str();
  }

  auto operator<=>(const st_box &) const = default;
};
} // tmpofd
