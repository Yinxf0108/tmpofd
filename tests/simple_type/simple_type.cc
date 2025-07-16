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

#include "tmpofd/core/struct/common/simple_type.h"
#include "tmpofd/core/struct/ofd/ofd.h"
#include "tmpofd/core/struct/document/document.h"

using namespace tmpofd;

void test_st_bool() {
  static_assert(is_st_bool<st_bool>);
  static_assert(is_st_bool<const st_bool>);
  static_assert(is_st_bool<st_bool &>);
  static_assert(is_st_bool<const st_bool &>);

  static_assert(!is_st_bool<st_int>);
  static_assert(!is_st_bool<const st_int>);
  static_assert(!is_st_bool<st_int &>);
  static_assert(!is_st_bool<const st_int &>);

  static_assert(!is_st_bool<st_double>);
  static_assert(!is_st_bool<const st_double>);
  static_assert(!is_st_bool<st_double &>);
  static_assert(!is_st_bool<const st_double &>);

  static_assert(!is_st_bool<st_string>);
  static_assert(!is_st_bool<const st_string>);
  static_assert(!is_st_bool<st_string &>);
  static_assert(!is_st_bool<const st_string &>);

  static_assert(!is_st_bool<st_vector<std::monostate> >);
  static_assert(!is_st_bool<const st_vector<std::monostate>>);
  static_assert(!is_st_bool<st_vector<std::monostate> &>);
  static_assert(!is_st_bool<const st_vector<std::monostate> &>);

  static_assert(!is_st_bool<st_date>);
  static_assert(!is_st_bool<const st_date>);
  static_assert(!is_st_bool<st_date &>);
  static_assert(!is_st_bool<const st_date &>);

  static_assert(!is_st_bool<st_date_time>);
  static_assert(!is_st_bool<const st_date_time>);
  static_assert(!is_st_bool<st_date_time &>);
  static_assert(!is_st_bool<const st_date_time &>);

  static_assert(!is_st_bool<st_loc>);
  static_assert(!is_st_bool<const st_loc>);
  static_assert(!is_st_bool<st_loc &>);
  static_assert(!is_st_bool<const st_loc &>);

  static_assert(!is_st_bool<st_array<st_id> >);
  static_assert(!is_st_bool<const st_array<st_id>>);
  static_assert(!is_st_bool<st_array<st_id> &>);
  static_assert(!is_st_bool<const st_array<st_id> &>);

  static_assert(!is_st_bool<st_id>);
  static_assert(!is_st_bool<const st_id>);
  static_assert(!is_st_bool<st_id &>);
  static_assert(!is_st_bool<const st_id &>);

  static_assert(!is_st_bool<st_ref_id>);
  static_assert(!is_st_bool<const st_ref_id>);
  static_assert(!is_st_bool<st_ref_id &>);
  static_assert(!is_st_bool<const st_ref_id &>);

  static_assert(!is_st_bool<st_pos<st_int> >);
  static_assert(!is_st_bool<const st_pos<st_int>>);
  static_assert(!is_st_bool<st_pos<st_int> &>);
  static_assert(!is_st_bool<const st_pos<st_int> &>);

  static_assert(!is_st_bool<st_box<st_int> >);
  static_assert(!is_st_bool<const st_box<st_int>>);
  static_assert(!is_st_bool<st_box<st_int> &>);
  static_assert(!is_st_bool<const st_box<st_int> &>);
}

void test_st_int() {
  static_assert(!is_st_int<st_bool>);
  static_assert(!is_st_int<const st_bool>);
  static_assert(!is_st_int<st_bool &>);
  static_assert(!is_st_int<const st_bool &>);

  static_assert(is_st_int<st_int>);
  static_assert(is_st_int<const st_int>);
  static_assert(is_st_int<st_int &>);
  static_assert(is_st_int<const st_int &>);

  static_assert(!is_st_int<st_double>);
  static_assert(!is_st_int<const st_double>);
  static_assert(!is_st_int<st_double &>);
  static_assert(!is_st_int<const st_double &>);

  static_assert(!is_st_int<st_string>);
  static_assert(!is_st_int<const st_string>);
  static_assert(!is_st_int<st_string &>);
  static_assert(!is_st_int<const st_string &>);

  static_assert(!is_st_int<st_vector<std::monostate> >);
  static_assert(!is_st_int<const st_vector<std::monostate>>);
  static_assert(!is_st_int<st_vector<std::monostate> &>);
  static_assert(!is_st_int<const st_vector<std::monostate> &>);

  static_assert(!is_st_int<st_date>);
  static_assert(!is_st_int<const st_date>);
  static_assert(!is_st_int<st_date &>);
  static_assert(!is_st_int<const st_date &>);

  static_assert(!is_st_int<st_date_time>);
  static_assert(!is_st_int<const st_date_time>);
  static_assert(!is_st_int<st_date_time &>);
  static_assert(!is_st_int<const st_date_time &>);

  static_assert(!is_st_int<st_loc>);
  static_assert(!is_st_int<const st_loc>);
  static_assert(!is_st_int<st_loc &>);
  static_assert(!is_st_int<const st_loc &>);

  static_assert(!is_st_int<st_array<st_id> >);
  static_assert(!is_st_int<const st_array<st_id>>);
  static_assert(!is_st_int<st_array<st_id> &>);
  static_assert(!is_st_int<const st_array<st_id> &>);

  static_assert(!is_st_int<st_id>);
  static_assert(!is_st_int<const st_id>);
  static_assert(!is_st_int<st_id &>);
  static_assert(!is_st_int<const st_id &>);

  static_assert(!is_st_int<st_ref_id>);
  static_assert(!is_st_int<const st_ref_id>);
  static_assert(!is_st_int<st_ref_id &>);
  static_assert(!is_st_int<const st_ref_id &>);

  static_assert(!is_st_int<st_pos<st_int> >);
  static_assert(!is_st_int<const st_pos<st_int>>);
  static_assert(!is_st_int<st_pos<st_int> &>);
  static_assert(!is_st_int<const st_pos<st_int> &>);

  static_assert(!is_st_int<st_box<st_int> >);
  static_assert(!is_st_int<const st_box<st_int>>);
  static_assert(!is_st_int<st_box<st_int> &>);
  static_assert(!is_st_int<const st_box<st_int> &>);
}

void test_floating_t() {
  static_assert(!is_floating_t<st_bool>);
  static_assert(!is_floating_t<const st_bool>);
  static_assert(!is_floating_t<st_bool &>);
  static_assert(!is_floating_t<const st_bool &>);

  static_assert(!is_floating_t<st_int>);
  static_assert(!is_floating_t<const st_int>);
  static_assert(!is_floating_t<st_int &>);
  static_assert(!is_floating_t<const st_int &>);

  static_assert(is_floating_t<st_double>);
  static_assert(is_floating_t<const st_double>);
  static_assert(is_floating_t<st_double &>);
  static_assert(is_floating_t<const st_double &>);

  static_assert(!is_floating_t<st_string>);
  static_assert(!is_floating_t<const st_string>);
  static_assert(!is_floating_t<st_string &>);
  static_assert(!is_floating_t<const st_string &>);

  static_assert(!is_floating_t<st_vector<std::monostate> >);
  static_assert(!is_floating_t<const st_vector<std::monostate>>);
  static_assert(!is_floating_t<st_vector<std::monostate> &>);
  static_assert(!is_floating_t<const st_vector<std::monostate> &>);

  static_assert(!is_floating_t<st_date>);
  static_assert(!is_floating_t<const st_date>);
  static_assert(!is_floating_t<st_date &>);
  static_assert(!is_floating_t<const st_date &>);

  static_assert(!is_floating_t<st_date_time>);
  static_assert(!is_floating_t<const st_date_time>);
  static_assert(!is_floating_t<st_date_time &>);
  static_assert(!is_floating_t<const st_date_time &>);

  static_assert(!is_floating_t<st_loc>);
  static_assert(!is_floating_t<const st_loc>);
  static_assert(!is_floating_t<st_loc &>);
  static_assert(!is_floating_t<const st_loc &>);

  static_assert(!is_floating_t<st_array<st_id> >);
  static_assert(!is_floating_t<const st_array<st_id>>);
  static_assert(!is_floating_t<st_array<st_id> &>);
  static_assert(!is_floating_t<const st_array<st_id> &>);

  static_assert(!is_floating_t<st_id>);
  static_assert(!is_floating_t<const st_id>);
  static_assert(!is_floating_t<st_id &>);
  static_assert(!is_floating_t<const st_id &>);

  static_assert(!is_floating_t<st_ref_id>);
  static_assert(!is_floating_t<const st_ref_id>);
  static_assert(!is_floating_t<st_ref_id &>);
  static_assert(!is_floating_t<const st_ref_id &>);

  static_assert(!is_floating_t<st_pos<st_int> >);
  static_assert(!is_floating_t<const st_pos<st_int>>);
  static_assert(!is_floating_t<st_pos<st_int> &>);
  static_assert(!is_floating_t<const st_pos<st_int> &>);

  static_assert(!is_floating_t<st_box<st_int> >);
  static_assert(!is_floating_t<const st_box<st_int>>);
  static_assert(!is_floating_t<st_box<st_int> &>);
  static_assert(!is_floating_t<const st_box<st_int> &>);
}

void test_st_string() {
  static_assert(!is_st_string<st_bool>);
  static_assert(!is_st_string<const st_bool>);
  static_assert(!is_st_string<st_bool &>);
  static_assert(!is_st_string<const st_bool &>);

  static_assert(!is_st_string<st_int>);
  static_assert(!is_st_string<const st_int>);
  static_assert(!is_st_string<st_int &>);
  static_assert(!is_st_string<const st_int &>);

  static_assert(!is_st_string<st_double>);
  static_assert(!is_st_string<const st_double>);
  static_assert(!is_st_string<st_double &>);
  static_assert(!is_st_string<const st_double &>);

  static_assert(is_st_string<st_string>);
  static_assert(is_st_string<const st_string>);
  static_assert(is_st_string<st_string &>);
  static_assert(is_st_string<const st_string &>);

  static_assert(!is_st_string<st_vector<std::monostate> >);
  static_assert(!is_st_string<const st_vector<std::monostate>>);
  static_assert(!is_st_string<st_vector<std::monostate> &>);
  static_assert(!is_st_string<const st_vector<std::monostate> &>);

  static_assert(!is_st_string<st_date>);
  static_assert(!is_st_string<const st_date>);
  static_assert(!is_st_string<st_date &>);
  static_assert(!is_st_string<const st_date &>);

  static_assert(!is_st_string<st_date_time>);
  static_assert(!is_st_string<const st_date_time>);
  static_assert(!is_st_string<st_date_time &>);
  static_assert(!is_st_string<const st_date_time &>);

  static_assert(!is_st_string<st_loc>);
  static_assert(!is_st_string<const st_loc>);
  static_assert(!is_st_string<st_loc &>);
  static_assert(!is_st_string<const st_loc &>);

  static_assert(!is_st_string<st_array<st_id> >);
  static_assert(!is_st_string<const st_array<st_id>>);
  static_assert(!is_st_string<st_array<st_id> &>);
  static_assert(!is_st_string<const st_array<st_id> &>);

  static_assert(!is_st_string<st_id>);
  static_assert(!is_st_string<const st_id>);
  static_assert(!is_st_string<st_id &>);
  static_assert(!is_st_string<const st_id &>);

  static_assert(!is_st_string<st_ref_id>);
  static_assert(!is_st_string<const st_ref_id>);
  static_assert(!is_st_string<st_ref_id &>);
  static_assert(!is_st_string<const st_ref_id &>);

  static_assert(!is_st_string<st_pos<st_int> >);
  static_assert(!is_st_string<const st_pos<st_int>>);
  static_assert(!is_st_string<st_pos<st_int> &>);
  static_assert(!is_st_string<const st_pos<st_int> &>);

  static_assert(!is_st_string<st_box<st_int> >);
  static_assert(!is_st_string<const st_box<st_int>>);
  static_assert(!is_st_string<st_box<st_int> &>);
  static_assert(!is_st_string<const st_box<st_int> &>);
}

void test_st_vector() {
  static_assert(!is_st_vector<st_bool>);
  static_assert(!is_st_vector<const st_bool>);
  static_assert(!is_st_vector<st_bool &>);
  static_assert(!is_st_vector<const st_bool &>);

  static_assert(!is_st_vector<st_int>);
  static_assert(!is_st_vector<const st_int>);
  static_assert(!is_st_vector<st_int &>);
  static_assert(!is_st_vector<const st_int &>);

  static_assert(!is_st_vector<st_double>);
  static_assert(!is_st_vector<const st_double>);
  static_assert(!is_st_vector<st_double &>);
  static_assert(!is_st_vector<const st_double &>);

  static_assert(!is_st_vector<st_string>);
  static_assert(!is_st_vector<const st_string>);
  static_assert(!is_st_vector<st_string &>);
  static_assert(!is_st_vector<const st_string &>);

  static_assert(is_st_vector<st_vector<std::monostate> >);
  static_assert(is_st_vector<const st_vector<std::monostate>>);
  static_assert(is_st_vector<st_vector<std::monostate> &>);
  static_assert(is_st_vector<const st_vector<std::monostate> &>);

  static_assert(!is_st_vector<st_date>);
  static_assert(!is_st_vector<const st_date>);
  static_assert(!is_st_vector<st_date &>);
  static_assert(!is_st_vector<const st_date &>);

  static_assert(!is_st_vector<st_date_time>);
  static_assert(!is_st_vector<const st_date_time>);
  static_assert(!is_st_vector<st_date_time &>);
  static_assert(!is_st_vector<const st_date_time &>);

  static_assert(!is_st_vector<st_loc>);
  static_assert(!is_st_vector<const st_loc>);
  static_assert(!is_st_vector<st_loc &>);
  static_assert(!is_st_vector<const st_loc &>);

  static_assert(!is_st_vector<st_array<st_id> >);
  static_assert(!is_st_vector<const st_array<st_id>>);
  static_assert(!is_st_vector<st_array<st_id> &>);
  static_assert(!is_st_vector<const st_array<st_id> &>);

  static_assert(!is_st_vector<st_id>);
  static_assert(!is_st_vector<const st_id>);
  static_assert(!is_st_vector<st_id &>);
  static_assert(!is_st_vector<const st_id &>);

  static_assert(!is_st_vector<st_ref_id>);
  static_assert(!is_st_vector<const st_ref_id>);
  static_assert(!is_st_vector<st_ref_id &>);
  static_assert(!is_st_vector<const st_ref_id &>);

  static_assert(!is_st_vector<st_pos<st_int> >);
  static_assert(!is_st_vector<const st_pos<st_int>>);
  static_assert(!is_st_vector<st_pos<st_int> &>);
  static_assert(!is_st_vector<const st_pos<st_int> &>);

  static_assert(!is_st_vector<st_box<st_int> >);
  static_assert(!is_st_vector<const st_box<st_int>>);
  static_assert(!is_st_vector<st_box<st_int> &>);
  static_assert(!is_st_vector<const st_box<st_int> &>);
}

void test_st_date() {
  static_assert(!is_st_date<st_bool>);
  static_assert(!is_st_date<const st_bool>);
  static_assert(!is_st_date<st_bool &>);
  static_assert(!is_st_date<const st_bool &>);

  static_assert(!is_st_date<st_int>);
  static_assert(!is_st_date<const st_int>);
  static_assert(!is_st_date<st_int &>);
  static_assert(!is_st_date<const st_int &>);

  static_assert(!is_st_date<st_double>);
  static_assert(!is_st_date<const st_double>);
  static_assert(!is_st_date<st_double &>);
  static_assert(!is_st_date<const st_double &>);

  static_assert(!is_st_date<st_string>);
  static_assert(!is_st_date<const st_string>);
  static_assert(!is_st_date<st_string &>);
  static_assert(!is_st_date<const st_string &>);

  static_assert(!is_st_date<st_vector<std::monostate> >);
  static_assert(!is_st_date<const st_vector<std::monostate>>);
  static_assert(!is_st_date<st_vector<std::monostate> &>);
  static_assert(!is_st_date<const st_vector<std::monostate> &>);

  static_assert(is_st_date<st_date>);
  static_assert(is_st_date<const st_date>);
  static_assert(is_st_date<st_date &>);
  static_assert(is_st_date<const st_date &>);

  static_assert(!is_st_date<st_date_time>);
  static_assert(!is_st_date<const st_date_time>);
  static_assert(!is_st_date<st_date_time &>);
  static_assert(!is_st_date<const st_date_time &>);

  static_assert(!is_st_date<st_loc>);
  static_assert(!is_st_date<const st_loc>);
  static_assert(!is_st_date<st_loc &>);
  static_assert(!is_st_date<const st_loc &>);

  static_assert(!is_st_date<st_array<st_id> >);
  static_assert(!is_st_date<const st_array<st_id>>);
  static_assert(!is_st_date<st_array<st_id> &>);
  static_assert(!is_st_date<const st_array<st_id> &>);

  static_assert(!is_st_date<st_id>);
  static_assert(!is_st_date<const st_id>);
  static_assert(!is_st_date<st_id &>);
  static_assert(!is_st_date<const st_id &>);

  static_assert(!is_st_date<st_ref_id>);
  static_assert(!is_st_date<const st_ref_id>);
  static_assert(!is_st_date<st_ref_id &>);
  static_assert(!is_st_date<const st_ref_id &>);

  static_assert(!is_st_date<st_pos<st_int> >);
  static_assert(!is_st_date<const st_pos<st_int>>);
  static_assert(!is_st_date<st_pos<st_int> &>);
  static_assert(!is_st_date<const st_pos<st_int> &>);

  static_assert(!is_st_date<st_box<st_int> >);
  static_assert(!is_st_date<const st_box<st_int>>);
  static_assert(!is_st_date<st_box<st_int> &>);
  static_assert(!is_st_date<const st_box<st_int> &>);
}

void test_st_date_time() {
  static_assert(!is_st_date_time<st_bool>);
  static_assert(!is_st_date_time<const st_bool>);
  static_assert(!is_st_date_time<st_bool &>);
  static_assert(!is_st_date_time<const st_bool &>);

  static_assert(!is_st_date_time<st_int>);
  static_assert(!is_st_date_time<const st_int>);
  static_assert(!is_st_date_time<st_int &>);
  static_assert(!is_st_date_time<const st_int &>);

  static_assert(!is_st_date_time<st_double>);
  static_assert(!is_st_date_time<const st_double>);
  static_assert(!is_st_date_time<st_double &>);
  static_assert(!is_st_date_time<const st_double &>);

  static_assert(!is_st_date_time<st_string>);
  static_assert(!is_st_date_time<const st_string>);
  static_assert(!is_st_date_time<st_string &>);
  static_assert(!is_st_date_time<const st_string &>);

  static_assert(!is_st_date_time<st_vector<std::monostate> >);
  static_assert(!is_st_date_time<const st_vector<std::monostate>>);
  static_assert(!is_st_date_time<st_vector<std::monostate> &>);
  static_assert(!is_st_date_time<const st_vector<std::monostate> &>);

  static_assert(!is_st_date_time<st_date>);
  static_assert(!is_st_date_time<const st_date>);
  static_assert(!is_st_date_time<st_date &>);
  static_assert(!is_st_date_time<const st_date &>);

  static_assert(is_st_date_time<st_date_time>);
  static_assert(is_st_date_time<const st_date_time>);
  static_assert(is_st_date_time<st_date_time &>);
  static_assert(is_st_date_time<const st_date_time &>);

  static_assert(!is_st_date_time<st_loc>);
  static_assert(!is_st_date_time<const st_loc>);
  static_assert(!is_st_date_time<st_loc &>);
  static_assert(!is_st_date_time<const st_loc &>);

  static_assert(!is_st_date_time<st_array<st_id> >);
  static_assert(!is_st_date_time<const st_array<st_id>>);
  static_assert(!is_st_date_time<st_array<st_id> &>);
  static_assert(!is_st_date_time<const st_array<st_id> &>);

  static_assert(!is_st_date_time<st_id>);
  static_assert(!is_st_date_time<const st_id>);
  static_assert(!is_st_date_time<st_id &>);
  static_assert(!is_st_date_time<const st_id &>);

  static_assert(!is_st_date_time<st_ref_id>);
  static_assert(!is_st_date_time<const st_ref_id>);
  static_assert(!is_st_date_time<st_ref_id &>);
  static_assert(!is_st_date_time<const st_ref_id &>);

  static_assert(!is_st_date_time<st_pos<st_int> >);
  static_assert(!is_st_date_time<const st_pos<st_int>>);
  static_assert(!is_st_date_time<st_pos<st_int> &>);
  static_assert(!is_st_date_time<const st_pos<st_int> &>);

  static_assert(!is_st_date_time<st_box<st_int> >);
  static_assert(!is_st_date_time<const st_box<st_int>>);
  static_assert(!is_st_date_time<st_box<st_int> &>);
  static_assert(!is_st_date_time<const st_box<st_int> &>);
}

void test_st_loc() {
  static_assert(!is_st_loc<st_bool>);
  static_assert(!is_st_loc<const st_bool>);
  static_assert(!is_st_loc<st_bool &>);
  static_assert(!is_st_loc<const st_bool &>);

  static_assert(!is_st_loc<st_int>);
  static_assert(!is_st_loc<const st_int>);
  static_assert(!is_st_loc<st_int &>);
  static_assert(!is_st_loc<const st_int &>);

  static_assert(!is_st_loc<st_double>);
  static_assert(!is_st_loc<const st_double>);
  static_assert(!is_st_loc<st_double &>);
  static_assert(!is_st_loc<const st_double &>);

  static_assert(!is_st_loc<st_string>);
  static_assert(!is_st_loc<const st_string>);
  static_assert(!is_st_loc<st_string &>);
  static_assert(!is_st_loc<const st_string &>);

  static_assert(!is_st_loc<st_vector<std::monostate> >);
  static_assert(!is_st_loc<const st_vector<std::monostate>>);
  static_assert(!is_st_loc<st_vector<std::monostate> &>);
  static_assert(!is_st_loc<const st_vector<std::monostate> &>);

  static_assert(!is_st_loc<st_date>);
  static_assert(!is_st_loc<const st_date>);
  static_assert(!is_st_loc<st_date &>);
  static_assert(!is_st_loc<const st_date &>);

  static_assert(!is_st_loc<st_date_time>);
  static_assert(!is_st_loc<const st_date_time>);
  static_assert(!is_st_loc<st_date_time &>);
  static_assert(!is_st_loc<const st_date_time &>);

  static_assert(is_st_loc<st_loc>);
  static_assert(is_st_loc<const st_loc>);
  static_assert(is_st_loc<st_loc &>);
  static_assert(is_st_loc<const st_loc &>);

  static_assert(!is_st_loc<st_array<st_id> >);
  static_assert(!is_st_loc<const st_array<st_id>>);
  static_assert(!is_st_loc<st_array<st_id> &>);
  static_assert(!is_st_loc<const st_array<st_id> &>);

  static_assert(!is_st_loc<st_id>);
  static_assert(!is_st_loc<const st_id>);
  static_assert(!is_st_loc<st_id &>);
  static_assert(!is_st_loc<const st_id &>);

  static_assert(!is_st_loc<st_ref_id>);
  static_assert(!is_st_loc<const st_ref_id>);
  static_assert(!is_st_loc<st_ref_id &>);
  static_assert(!is_st_loc<const st_ref_id &>);

  static_assert(!is_st_loc<st_pos<st_int> >);
  static_assert(!is_st_loc<const st_pos<st_int>>);
  static_assert(!is_st_loc<st_pos<st_int> &>);
  static_assert(!is_st_loc<const st_pos<st_int> &>);

  static_assert(!is_st_loc<st_box<st_int> >);
  static_assert(!is_st_loc<const st_box<st_int>>);
  static_assert(!is_st_loc<st_box<st_int> &>);
  static_assert(!is_st_loc<const st_box<st_int> &>);
}

void test_st_array() {
  static_assert(!is_st_array<st_bool>);
  static_assert(!is_st_array<const st_bool>);
  static_assert(!is_st_array<st_bool &>);
  static_assert(!is_st_array<const st_bool &>);

  static_assert(!is_st_array<st_int>);
  static_assert(!is_st_array<const st_int>);
  static_assert(!is_st_array<st_int &>);
  static_assert(!is_st_array<const st_int &>);

  static_assert(!is_st_array<st_double>);
  static_assert(!is_st_array<const st_double>);
  static_assert(!is_st_array<st_double &>);
  static_assert(!is_st_array<const st_double &>);

  static_assert(!is_st_array<st_string>);
  static_assert(!is_st_array<const st_string>);
  static_assert(!is_st_array<st_string &>);
  static_assert(!is_st_array<const st_string &>);

  static_assert(!is_st_array<st_vector<std::monostate> >);
  static_assert(!is_st_array<const st_vector<std::monostate>>);
  static_assert(!is_st_array<st_vector<std::monostate> &>);
  static_assert(!is_st_array<const st_vector<std::monostate> &>);

  static_assert(!is_st_array<st_date>);
  static_assert(!is_st_array<const st_date>);
  static_assert(!is_st_array<st_date &>);
  static_assert(!is_st_array<const st_date &>);

  static_assert(!is_st_array<st_date_time>);
  static_assert(!is_st_array<const st_date_time>);
  static_assert(!is_st_array<st_date_time &>);
  static_assert(!is_st_array<const st_date_time &>);

  static_assert(!is_st_array<st_loc>);
  static_assert(!is_st_array<const st_loc>);
  static_assert(!is_st_array<st_loc &>);
  static_assert(!is_st_array<const st_loc &>);

  static_assert(is_st_array<st_array<st_id> >);
  static_assert(is_st_array<const st_array<st_id>>);
  static_assert(is_st_array<st_array<st_id> &>);
  static_assert(is_st_array<const st_array<st_id> &>);

  static_assert(!is_st_array<st_id>);
  static_assert(!is_st_array<const st_id>);
  static_assert(!is_st_array<st_id &>);
  static_assert(!is_st_array<const st_id &>);

  static_assert(!is_st_array<st_ref_id>);
  static_assert(!is_st_array<const st_ref_id>);
  static_assert(!is_st_array<st_ref_id &>);
  static_assert(!is_st_array<const st_ref_id &>);

  static_assert(!is_st_array<st_pos<st_int> >);
  static_assert(!is_st_array<const st_pos<st_int>>);
  static_assert(!is_st_array<st_pos<st_int> &>);
  static_assert(!is_st_array<const st_pos<st_int> &>);

  static_assert(!is_st_array<st_box<st_int> >);
  static_assert(!is_st_array<const st_box<st_int>>);
  static_assert(!is_st_array<st_box<st_int> &>);
  static_assert(!is_st_array<const st_box<st_int> &>);
}

void test_st_id() {
  static_assert(!is_st_id<st_bool>);
  static_assert(!is_st_id<const st_bool>);
  static_assert(!is_st_id<st_bool &>);
  static_assert(!is_st_id<const st_bool &>);

  static_assert(!is_st_id<st_int>);
  static_assert(!is_st_id<const st_int>);
  static_assert(!is_st_id<st_int &>);
  static_assert(!is_st_id<const st_int &>);

  static_assert(!is_st_id<st_double>);
  static_assert(!is_st_id<const st_double>);
  static_assert(!is_st_id<st_double &>);
  static_assert(!is_st_id<const st_double &>);

  static_assert(!is_st_id<st_string>);
  static_assert(!is_st_id<const st_string>);
  static_assert(!is_st_id<st_string &>);
  static_assert(!is_st_id<const st_string &>);

  static_assert(!is_st_id<st_vector<std::monostate> >);
  static_assert(!is_st_id<const st_vector<std::monostate>>);
  static_assert(!is_st_id<st_vector<std::monostate> &>);
  static_assert(!is_st_id<const st_vector<std::monostate> &>);

  static_assert(!is_st_id<st_date>);
  static_assert(!is_st_id<const st_date>);
  static_assert(!is_st_id<st_date &>);
  static_assert(!is_st_id<const st_date &>);

  static_assert(!is_st_id<st_date_time>);
  static_assert(!is_st_id<const st_date_time>);
  static_assert(!is_st_id<st_date_time &>);
  static_assert(!is_st_id<const st_date_time &>);

  static_assert(!is_st_id<st_loc>);
  static_assert(!is_st_id<const st_loc>);
  static_assert(!is_st_id<st_loc &>);
  static_assert(!is_st_id<const st_loc &>);

  static_assert(!is_st_id<st_array<st_id> >);
  static_assert(!is_st_id<const st_array<st_id>>);
  static_assert(!is_st_id<st_array<st_id> &>);
  static_assert(!is_st_id<const st_array<st_id> &>);

  static_assert(is_st_id<st_id>);
  static_assert(is_st_id<const st_id>);
  static_assert(is_st_id<st_id &>);
  static_assert(is_st_id<const st_id &>);

  static_assert(is_st_id<st_ref_id>);
  static_assert(is_st_id<const st_ref_id>);
  static_assert(is_st_id<st_ref_id &>);
  static_assert(is_st_id<const st_ref_id &>);

  static_assert(!is_st_id<st_pos<st_int> >);
  static_assert(!is_st_id<const st_pos<st_int>>);
  static_assert(!is_st_id<st_pos<st_int> &>);
  static_assert(!is_st_id<const st_pos<st_int> &>);

  static_assert(!is_st_id<st_box<st_int> >);
  static_assert(!is_st_id<const st_box<st_int>>);
  static_assert(!is_st_id<st_box<st_int> &>);
  static_assert(!is_st_id<const st_box<st_int> &>);
}

void test_st_ref_id() {
  static_assert(!is_st_ref_id<st_bool>);
  static_assert(!is_st_ref_id<const st_bool>);
  static_assert(!is_st_ref_id<st_bool &>);
  static_assert(!is_st_ref_id<const st_bool &>);

  static_assert(!is_st_ref_id<st_int>);
  static_assert(!is_st_ref_id<const st_int>);
  static_assert(!is_st_ref_id<st_int &>);
  static_assert(!is_st_ref_id<const st_int &>);

  static_assert(!is_st_ref_id<st_double>);
  static_assert(!is_st_ref_id<const st_double>);
  static_assert(!is_st_ref_id<st_double &>);
  static_assert(!is_st_ref_id<const st_double &>);

  static_assert(!is_st_ref_id<st_string>);
  static_assert(!is_st_ref_id<const st_string>);
  static_assert(!is_st_ref_id<st_string &>);
  static_assert(!is_st_ref_id<const st_string &>);

  static_assert(!is_st_ref_id<st_vector<std::monostate> >);
  static_assert(!is_st_ref_id<const st_vector<std::monostate>>);
  static_assert(!is_st_ref_id<st_vector<std::monostate> &>);
  static_assert(!is_st_ref_id<const st_vector<std::monostate> &>);

  static_assert(!is_st_ref_id<st_date>);
  static_assert(!is_st_ref_id<const st_date>);
  static_assert(!is_st_ref_id<st_date &>);
  static_assert(!is_st_ref_id<const st_date &>);

  static_assert(!is_st_ref_id<st_date_time>);
  static_assert(!is_st_ref_id<const st_date_time>);
  static_assert(!is_st_ref_id<st_date_time &>);
  static_assert(!is_st_ref_id<const st_date_time &>);

  static_assert(!is_st_ref_id<st_loc>);
  static_assert(!is_st_ref_id<const st_loc>);
  static_assert(!is_st_ref_id<st_loc &>);
  static_assert(!is_st_ref_id<const st_loc &>);

  static_assert(!is_st_ref_id<st_array<st_id> >);
  static_assert(!is_st_ref_id<const st_array<st_id>>);
  static_assert(!is_st_ref_id<st_array<st_id> &>);
  static_assert(!is_st_ref_id<const st_array<st_id> &>);

  static_assert(is_st_ref_id<st_id>);
  static_assert(is_st_ref_id<const st_id>);
  static_assert(is_st_ref_id<st_id &>);
  static_assert(is_st_ref_id<const st_id &>);

  static_assert(is_st_ref_id<st_ref_id>);
  static_assert(is_st_ref_id<const st_ref_id>);
  static_assert(is_st_ref_id<st_ref_id &>);
  static_assert(is_st_ref_id<const st_ref_id &>);

  static_assert(!is_st_ref_id<st_pos<st_int> >);
  static_assert(!is_st_ref_id<const st_pos<st_int>>);
  static_assert(!is_st_ref_id<st_pos<st_int> &>);
  static_assert(!is_st_ref_id<const st_pos<st_int> &>);

  static_assert(!is_st_ref_id<st_box<st_int> >);
  static_assert(!is_st_ref_id<const st_box<st_int>>);
  static_assert(!is_st_ref_id<st_box<st_int> &>);
  static_assert(!is_st_ref_id<const st_box<st_int> &>);
}

void test_st_pos() {
  static_assert(!is_st_pos<st_bool>);
  static_assert(!is_st_pos<const st_bool>);
  static_assert(!is_st_pos<st_bool &>);
  static_assert(!is_st_pos<const st_bool &>);

  static_assert(!is_st_pos<st_int>);
  static_assert(!is_st_pos<const st_int>);
  static_assert(!is_st_pos<st_int &>);
  static_assert(!is_st_pos<const st_int &>);

  static_assert(!is_st_pos<st_double>);
  static_assert(!is_st_pos<const st_double>);
  static_assert(!is_st_pos<st_double &>);
  static_assert(!is_st_pos<const st_double &>);

  static_assert(!is_st_pos<st_string>);
  static_assert(!is_st_pos<const st_string>);
  static_assert(!is_st_pos<st_string &>);
  static_assert(!is_st_pos<const st_string &>);

  static_assert(!is_st_pos<st_vector<std::monostate> >);
  static_assert(!is_st_pos<const st_vector<std::monostate>>);
  static_assert(!is_st_pos<st_vector<std::monostate> &>);
  static_assert(!is_st_pos<const st_vector<std::monostate> &>);

  static_assert(!is_st_pos<st_date>);
  static_assert(!is_st_pos<const st_date>);
  static_assert(!is_st_pos<st_date &>);
  static_assert(!is_st_pos<const st_date &>);

  static_assert(!is_st_pos<st_date_time>);
  static_assert(!is_st_pos<const st_date_time>);
  static_assert(!is_st_pos<st_date_time &>);
  static_assert(!is_st_pos<const st_date_time &>);

  static_assert(!is_st_pos<st_loc>);
  static_assert(!is_st_pos<const st_loc>);
  static_assert(!is_st_pos<st_loc &>);
  static_assert(!is_st_pos<const st_loc &>);

  static_assert(!is_st_pos<st_array<st_id> >);
  static_assert(!is_st_pos<const st_array<st_id>>);
  static_assert(!is_st_pos<st_array<st_id> &>);
  static_assert(!is_st_pos<const st_array<st_id> &>);

  static_assert(!is_st_pos<st_id>);
  static_assert(!is_st_pos<const st_id>);
  static_assert(!is_st_pos<st_id &>);
  static_assert(!is_st_pos<const st_id &>);

  static_assert(!is_st_pos<st_ref_id>);
  static_assert(!is_st_pos<const st_ref_id>);
  static_assert(!is_st_pos<st_ref_id &>);
  static_assert(!is_st_pos<const st_ref_id &>);

  static_assert(is_st_pos<st_pos<st_int> >);
  static_assert(is_st_pos<const st_pos<st_int>>);
  static_assert(is_st_pos<st_pos<st_int> &>);
  static_assert(is_st_pos<const st_pos<st_int> &>);

  static_assert(!is_st_pos<st_box<st_int> >);
  static_assert(!is_st_pos<const st_box<st_int>>);
  static_assert(!is_st_pos<st_box<st_int> &>);
  static_assert(!is_st_pos<const st_box<st_int> &>);
}

void test_st_box() {
  static_assert(!is_st_box<st_bool>);
  static_assert(!is_st_box<const st_bool>);
  static_assert(!is_st_box<st_bool &>);
  static_assert(!is_st_box<const st_bool &>);

  static_assert(!is_st_box<st_int>);
  static_assert(!is_st_box<const st_int>);
  static_assert(!is_st_box<st_int &>);
  static_assert(!is_st_box<const st_int &>);

  static_assert(!is_st_box<st_double>);
  static_assert(!is_st_box<const st_double>);
  static_assert(!is_st_box<st_double &>);
  static_assert(!is_st_box<const st_double &>);

  static_assert(!is_st_box<st_string>);
  static_assert(!is_st_box<const st_string>);
  static_assert(!is_st_box<st_string &>);
  static_assert(!is_st_box<const st_string &>);

  static_assert(!is_st_box<st_vector<std::monostate> >);
  static_assert(!is_st_box<const st_vector<std::monostate>>);
  static_assert(!is_st_box<st_vector<std::monostate> &>);
  static_assert(!is_st_box<const st_vector<std::monostate> &>);

  static_assert(!is_st_box<st_date>);
  static_assert(!is_st_box<const st_date>);
  static_assert(!is_st_box<st_date &>);
  static_assert(!is_st_box<const st_date &>);

  static_assert(!is_st_box<st_date_time>);
  static_assert(!is_st_box<const st_date_time>);
  static_assert(!is_st_box<st_date_time &>);
  static_assert(!is_st_box<const st_date_time &>);

  static_assert(!is_st_box<st_loc>);
  static_assert(!is_st_box<const st_loc>);
  static_assert(!is_st_box<st_loc &>);
  static_assert(!is_st_box<const st_loc &>);

  static_assert(!is_st_box<st_array<st_id> >);
  static_assert(!is_st_box<const st_array<st_id>>);
  static_assert(!is_st_box<st_array<st_id> &>);
  static_assert(!is_st_box<const st_array<st_id> &>);

  static_assert(!is_st_box<st_id>);
  static_assert(!is_st_box<const st_id>);
  static_assert(!is_st_box<st_id &>);
  static_assert(!is_st_box<const st_id &>);

  static_assert(!is_st_box<st_ref_id>);
  static_assert(!is_st_box<const st_ref_id>);
  static_assert(!is_st_box<st_ref_id &>);
  static_assert(!is_st_box<const st_ref_id &>);

  static_assert(!is_st_box<st_pos<st_int> >);
  static_assert(!is_st_box<const st_pos<st_int>>);
  static_assert(!is_st_box<st_pos<st_int> &>);
  static_assert(!is_st_box<const st_pos<st_int> &>);

  static_assert(is_st_box<st_box<st_int> >);
  static_assert(is_st_box<const st_box<st_int>>);
  static_assert(is_st_box<st_box<st_int> &>);
  static_assert(is_st_box<const st_box<st_int> &>);
}

void test_is_leaf_node() {
  static_assert(is_leaf_node<custom_data_t>);
  static_assert(is_leaf_node<const custom_data_t>);
  static_assert(is_leaf_node<custom_data_t &>);
  static_assert(is_leaf_node<const custom_data_t &>);

  static_assert(!is_leaf_node<ofd_t>);
  static_assert(!is_leaf_node<const ofd_t>);
  static_assert(!is_leaf_node<ofd_t &>);
  static_assert(!is_leaf_node<const ofd_t &>);
}

void test_is_unique_ptr() {
  auto ptr = std::make_unique<outline_elem_t>();
  const auto const_prt = std::make_unique<outline_elem_t>();
  [[maybe_unused]] auto &ref_ptr = ptr;
  [[maybe_unused]] const auto &const_ref_ptr = const_prt;

  static_assert(is_unique_ptr<decltype(ptr)>);
  static_assert(is_unique_ptr<decltype(const_prt)>);
  static_assert(is_unique_ptr<decltype(ref_ptr)>);
  static_assert(is_unique_ptr<decltype(const_ref_ptr)>);

  static_assert(!is_unique_ptr<decltype(*ptr)>);
  static_assert(!is_unique_ptr<decltype(*const_prt)>);
  static_assert(!is_unique_ptr<decltype(*ref_ptr)>);
  static_assert(!is_unique_ptr<decltype(*const_ref_ptr)>);

  static_assert(!is_unique_ptr<decltype(ptr.get())>);
  static_assert(!is_unique_ptr<decltype(const_prt.get())>);
  static_assert(!is_unique_ptr<decltype(ref_ptr.get())>);
  static_assert(!is_unique_ptr<decltype(const_ref_ptr.get())>);
}

int main() {
  test_st_bool();
  test_st_int();
  test_floating_t();
  test_st_string();
  test_st_vector();
  test_st_date();
  test_st_date_time();
  test_st_loc();
  test_st_array();
  test_st_id();
  test_st_ref_id();
  test_st_pos();
  test_st_box();

  test_is_leaf_node();
  test_is_unique_ptr();

  return 0;
}
