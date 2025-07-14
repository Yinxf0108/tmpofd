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

#include "tmpofd/core/struct/document/common_data.h"
#include "tmpofd/core/struct/document/pages.h"
#include "tmpofd/core/struct/document/permissions.h"
#include "tmpofd/core/struct/document/v_preferences.h"
#include "tmpofd/core/struct/common/complex_type.h"

namespace tmpofd {
struct actions_t {
  st_vector<action_t> action_;
};

REFLECT_STRUCT(
  ofd_namespace"Actions",
  actions_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Action", &actions_t::action_)
  )
)

struct outline_elem_t {
  st_string title_;
  std::optional<st_int> count_;
  std::optional<st_bool> expanded_;
  std::optional<actions_t> actions_;
  st_vector<std::unique_ptr<outline_elem_t> > outline_elem_;
};

REFLECT_STRUCT(
  ofd_namespace"OutlineElem",
  outline_elem_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Title", &outline_elem_t::title_),
    REFLECT_MEMBER("Count", &outline_elem_t::count_),
    REFLECT_MEMBER("Expanded", &outline_elem_t::expanded_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Actions", &outline_elem_t::actions_),
    REFLECT_MEMBER(ofd_namespace"OutlineElem", &outline_elem_t::outline_elem_)
  )
)

struct outlines_t {
  st_vector<outline_elem_t> outline_elem_;
};

REFLECT_STRUCT(
  ofd_namespace"Outlines",
  outlines_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"OutlineElem", &outlines_t::outline_elem_)
  )
)

struct bookmark_t {
  st_string name_;
  dest_t dest_;
};

REFLECT_STRUCT(
  ofd_namespace"Bookmark",
  bookmark_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Name", &bookmark_t::name_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Dest", &bookmark_t::dest_)
  )
)

struct bookmarks_t {
  st_vector<bookmark_t> bookmark_;
};

REFLECT_STRUCT(
  ofd_namespace"Bookmarks",
  bookmarks_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Bookmark", &bookmarks_t::bookmark_)
  )
)

struct document_t {
  common_data_t common_data_;
  pages_t pages_;
  std::optional<outlines_t> outlines_;
  std::optional<permission_t> permissions_;
  std::optional<actions_t> actions_;
  std::optional<v_preferences_t> v_preferences_;
  std::optional<bookmarks_t> bookmarks_;
  std::optional<st_loc> annotations_;
  std::optional<st_loc> custom_tags_;
  std::optional<st_loc> attachments_;
  std::optional<st_loc> extensions_;
};

REFLECT_STRUCT(
  ofd_namespace"Document",
  document_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"CommonData", &document_t::common_data_),
    REFLECT_MEMBER(ofd_namespace"Pages", &document_t::pages_),
    REFLECT_MEMBER(ofd_namespace"Outlines", &document_t::outlines_),
    REFLECT_MEMBER(ofd_namespace"Permissions", &document_t::permissions_),
    REFLECT_MEMBER(ofd_namespace"Actions", &document_t::actions_),
    REFLECT_MEMBER(ofd_namespace"VPreferences", &document_t::v_preferences_),
    REFLECT_MEMBER(ofd_namespace"Bookmarks", &document_t::bookmarks_),
    REFLECT_MEMBER(ofd_namespace"Annotations", &document_t::annotations_),
    REFLECT_MEMBER(ofd_namespace"CustomTags", &document_t::custom_tags_),
    REFLECT_MEMBER(ofd_namespace"Attachments", &document_t::attachments_),
    REFLECT_MEMBER(ofd_namespace"Extensions", &document_t::extensions_)
  )
)
} // tmpofd
