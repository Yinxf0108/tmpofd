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

#include "tmpofd/core/struct/common/simple_type.h"

#include <string_view>
#include <functional>
#include <tuple>

namespace tmpofd {
template<typename>
struct is_reflectable_trait : std::false_type {};

template<typename T>
concept is_reflectable = is_reflectable_trait<std::remove_cvref_t<T> >::value;

template<typename T>
struct member_t {
  std::string_view name_;
  T member_;

  constexpr member_t(const std::string_view name, T &&member) : name_(name), member_(std::forward<T>(member)) {}

  constexpr auto matched(const std::string_view name) const {
    constexpr std::string_view prefix(ofd_namespace);
    return name_ == name || (name_.starts_with(prefix) && name_.substr(prefix.length()) == name);
  }

  template<typename... Args>
  constexpr decltype(auto) invoke(Args &&... args) const {
    return std::invoke(this->member_, std::forward<Args>(args)...);
  }
};

template<typename>
struct struct_t;

template<typename T>
struct reflected_t {
  private:
    template<const auto &tuple, typename C>
    constexpr void get(const std::string_view name, C &&cb) const {
      if constexpr (0 < std::tuple_size_v<std::decay_t<decltype(tuple)>>) {
        [&]<std::size_t... i>(std::index_sequence<i...>) {
          ((std::get<i>(tuple).matched(name) ? (cb(std::get<i>(tuple)), true) : false) || ...);
        }(std::make_index_sequence<std::tuple_size_v<std::decay_t<decltype(tuple)>> >());
      }
    }

    template<const auto &tuple, typename C>
    constexpr void for_each(C &&cb) const {
      if constexpr (0 < std::tuple_size_v<std::decay_t<decltype(tuple)>>) {
        [&]<std::size_t... i>(std::index_sequence<i...>) {
          (cb(std::get<i>(tuple)), ...);
        }(std::make_index_sequence<std::tuple_size_v<std::decay_t<decltype(tuple)>> >());
      }
    }

  public:
    constexpr auto name() const { return struct_t<T>::name_; }

    constexpr auto attr_size() const { return std::tuple_size_v<decltype(struct_t<T>::attrs_)>; }

    template<typename C>
    constexpr void attr(const std::string_view name, C &&cb) const {
      get<struct_t<T>::attrs_>(name, std::forward<C>(cb));
    }

    template<typename C>
    constexpr void each_attr(C &&cb) const {
      for_each<struct_t<T>::attrs_>(std::forward<C>(cb));
    }

    constexpr auto node_size() const { return std::tuple_size_v<decltype(struct_t<T>::nodes_)>; }

    template<typename C>
    constexpr void node(const std::string_view name, C &&cb) const {
      get<struct_t<T>::nodes_>(name, std::forward<C>(cb));
    }

    template<typename C>
    constexpr void each_node(C &&cb) const {
      for_each<struct_t<T>::nodes_>(std::forward<C>(cb));
    }
};

#define REFLECT_MEMBER(name, member) member_t{name, member}

#define REFLECT_ATTR(...) inline static constexpr auto attrs_ = std::make_tuple(__VA_ARGS__);
#define REFLECT_NODE(...) inline static constexpr auto nodes_ = std::make_tuple(__VA_ARGS__);

#define REFLECT_STRUCT(name, member, ...)                    \
template<>                                                   \
struct is_reflectable_trait<member> : std::true_type {};     \
                                                             \
template<>                                                   \
struct struct_t<member> {                                    \
  static constexpr std::string_view name_ = name;            \
  __VA_ARGS__                                                \
};                                                           \
                                                             \
constexpr auto get_reflected(const member &mb) {             \
  return reflected_t<std::remove_cvref_t<decltype(mb)> >{};  \
}
} // tmpofd
