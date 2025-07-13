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

#include "tmpofd/core/struct/common/simple_type_fwd.h"
#include "tmpofd/core/struct/common/enum_string_type.h"

namespace tmpofd {
template<typename T>
concept is_st_bool = std::same_as<st_bool, remove_opt_t<std::remove_cvref_t<T> > >;

template<typename T>
concept is_st_int = std::same_as<st_int, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename T>
concept is_st_float = std::same_as<st_float, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename T>
concept is_st_double = std::same_as<st_double, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename T>
concept is_st_number = is_st_int<T> || is_st_float<T> || is_st_double<T>;

template<typename T>
concept is_st_string = std::same_as<st_string, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename>
struct is_st_vector_trait : std::false_type {};

template<typename T, typename Allocator>
struct is_st_vector_trait<st_vector<T, Allocator> > : std::true_type {};

template<typename T>
concept is_st_vector = is_st_vector_trait<remove_opt_t<std::remove_cvref_t<T>> >::value;

template<typename T>
concept is_st_date = std::same_as<st_date, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename T>
concept is_st_date_time = std::same_as<st_date_time, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename T>
concept is_st_loc = std::same_as<st_loc, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename>
struct is_st_array_trait : std::false_type {};

template<typename T>
struct is_st_array_trait<st_array<T> > : std::true_type {};

template<typename T>
concept is_st_array = is_st_array_trait<remove_opt_t<std::remove_cvref_t<T>> >::value;

template<typename T>
concept is_st_id = std::same_as<st_id, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename T>
concept is_st_ref_id = std::same_as<st_ref_id, remove_opt_t<std::remove_cvref_t<T>> >;

template<typename>
struct is_st_pos_trait : std::false_type {};

template<is_number T>
struct is_st_pos_trait<st_pos<T> > : std::true_type {};

template<typename T>
concept is_st_pos = is_st_pos_trait<remove_opt_t<std::remove_cvref_t<T>> >::value;

template<typename>
struct is_st_box_trait : std::false_type {};

template<is_number T>
struct is_st_box_trait<st_box<T> > : std::true_type {};

template<typename T>
concept is_st_box = is_st_box_trait<remove_opt_t<std::remove_cvref_t<T>> >::value;

template<typename T>
concept is_base_type = is_st_bool<T> || is_st_number<T> || is_st_string<T> || is_st_date<T> || is_st_date_time<T>
    || is_st_loc<T> || is_st_array<T> || is_st_id<T> || is_st_ref_id<T> || is_st_pos<T> || is_st_box<T>;

template<typename>
struct is_enum_string_trait : std::false_type {};

template<typename T>
struct is_enum_string_trait<enum_string_t<T> > : std::true_type {};

template<typename T>
concept is_enum_string = is_enum_string_trait<remove_opt_t<std::remove_cvref_t<T> > >::value;

template<typename T>
concept can_passed_via_string_view = is_st_string<T> || is_string_view<T> || is_st_loc<T> || is_enum_string<T>;

template<typename T>
concept is_time = is_st_date<T> || is_st_date_time<T>;

template<typename T>
concept is_id = is_st_id<T> || is_st_ref_id<T>;

template<typename T>
concept has_from_string = is_st_array<T> || is_st_pos<T> || is_st_box<T>;

template<typename, typename = std::void_t<> >
struct is_leaf_node_trait : std::false_type {};

template<typename T>
struct is_leaf_node_trait<T, std::void_t<decltype(std::declval<T>().leaf_value)> > : std::true_type {};

template<typename T>
concept is_leaf_node = is_leaf_node_trait<remove_opt_t<std::remove_cvref_t<T>> >::value;
} // tmpofd
