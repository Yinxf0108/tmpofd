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

#include <concepts>
#include <type_traits>
#include <string>
#include <vector>
#include <optional>

namespace tmpofd {
template<typename>
struct is_optional_trait : std::false_type {};

template<typename T>
struct is_optional_trait<std::optional<T> > : std::true_type {};

template<typename T>
concept is_optional = is_optional_trait<std::remove_cvref_t<T> >::value;

template<typename T>
struct remove_opt {
  using type = T;
};

template<typename T>
struct remove_opt<std::optional<T> > {
  using type = T;
};

template<typename T>
using remove_opt_t = typename remove_opt<T>::type;

template<typename T>
concept is_number = std::integral<T> || std::floating_point<T>;

template<typename T>
concept is_string = std::same_as<std::string, remove_opt_t<std::remove_cvref_t<T> > >;

template<typename T>
concept is_string_view = std::same_as<std::string_view, remove_opt_t<std::remove_cvref_t<T> > >;

template<typename>
struct is_vector_trait : std::false_type {};

template<typename T, typename Allocator>
struct is_vector_trait<std::vector<T, Allocator> > : std::true_type {};

template<typename T>
concept is_vector = is_vector_trait<remove_opt_t<std::remove_cvref_t<T> > >::value;
} // tmpofd
