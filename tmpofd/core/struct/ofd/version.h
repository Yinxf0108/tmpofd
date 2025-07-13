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
struct version_t {
  st_id id_;
  st_int index_;
  std::optional<st_bool> current_;
  st_loc base_loc_;
};

REFLECT_STRUCT(
  ofd_namespace"Version",
  version_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ID", &version_t::id_),
    REFLECT_MEMBER("Index", &version_t::index_),
    REFLECT_MEMBER("Current", &version_t::current_),
    REFLECT_MEMBER("BaseLoc", &version_t::base_loc_)
  )
  REFLECT_NODE()
)
} // tmpofd
