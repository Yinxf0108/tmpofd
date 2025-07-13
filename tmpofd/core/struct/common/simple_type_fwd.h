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

#include "tmpofd/core/traits/traits.h"

#include <chrono>
#include <filesystem>

namespace tmpofd {
template<typename>
inline constexpr bool always_false_v = false;

using st_bool = bool;
using st_int = int;
using st_float = float;
using st_double = double;
using st_string = std::string;
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
template<typename T> requires (!std::same_as<st_loc, remove_opt_t<std::remove_cvref_t<T>> > && !is_vector<T>)
struct st_array;

/**
* 标识，无符号整数，应在文档内唯一。0表示无效标识
*/
struct st_id;

/**
* 标识引用，无符号整数，此标识应为文档内已定义的标识
*/
struct st_ref_id;

/**
* 点坐标，以空格分割，前者为x值，后者为y值，可以是整数或者浮点数
*/
template<is_number T>
struct st_pos;

/**
* 矩形区域，以空格分割，前两个值代表了该矩形的左上角的坐标，后两个值依次表示该矩形的宽和高，可以是整数或者浮点数，后两个值应大于0
*/
template<is_number T>
struct st_box;
} // tmpofd
