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

namespace tmpofd {
struct print_permission_t {
  st_bool printable_;
  std::optional<st_int> copies_;
};

REFLECT_STRUCT(
    ofd_namespace"Print",
    print_permission_t,
    REFLECT_ATTR(
        REFLECT_MEMBER("Printable", &print_permission_t::printable_),
        REFLECT_MEMBER("Copies", &print_permission_t::copies_)
    )
    REFLECT_NODE()
)

struct valid_period_t {
  std::optional<st_date_time> start_date_;
  std::optional<st_date_time> end_date_;
};

REFLECT_STRUCT(
    ofd_namespace"ValidPeriod",
    valid_period_t,
    REFLECT_ATTR(
        REFLECT_MEMBER("StartDate", &valid_period_t::start_date_),
        REFLECT_MEMBER("EndDate", &valid_period_t::end_date_)
    )
    REFLECT_NODE()
)

struct permission_t {
  std::optional<st_bool> edit_;
  std::optional<st_bool> annot_;
  std::optional<st_bool> export_;
  std::optional<st_bool> signature_;
  std::optional<st_bool> watermark_;
  std::optional<st_bool> print_screen_;
  std::optional<print_permission_t> print_;
  std::optional<valid_period_t> valid_period_;
};

REFLECT_STRUCT(
    ofd_namespace"Permissions",
    permission_t,
    REFLECT_ATTR()
    REFLECT_NODE(
        REFLECT_MEMBER(ofd_namespace"Edit", &permission_t::edit_),
        REFLECT_MEMBER(ofd_namespace"Annot", &permission_t::annot_),
        REFLECT_MEMBER(ofd_namespace"Export", &permission_t::export_),
        REFLECT_MEMBER(ofd_namespace"Signature", &permission_t::signature_),
        REFLECT_MEMBER(ofd_namespace"Watermark", &permission_t::watermark_),
        REFLECT_MEMBER(ofd_namespace"PrintScreen", &permission_t::print_screen_),
        REFLECT_MEMBER(ofd_namespace"Print", &permission_t::print_),
        REFLECT_MEMBER(ofd_namespace"ValidPeriod", &permission_t::valid_period_)
    )
)

} // tmpofd
