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
enum class page_mode_t {
  None, FullScreen, UseOutlines, UseThumbs, UseCustomTags, UseLayers, UseAttatchs, UseBookmarks
};
template<>
struct enum_converter<page_mode_t> {
  static std::string to_string(const page_mode_t e) {
    switch (e) {
      case page_mode_t::None: return "None";
      case page_mode_t::FullScreen: return "FullScreen";
      case page_mode_t::UseOutlines: return "UseOutlines";
      case page_mode_t::UseThumbs: return "UseThumbs";
      case page_mode_t::UseCustomTags: return "UseCustomTags";
      case page_mode_t::UseLayers: return "UseLayers";
      case page_mode_t::UseAttatchs: return "UseAttatchs";
      case page_mode_t::UseBookmarks: return "UseBookmarks";
    }
    return "";
  }
  static std::optional<page_mode_t> from_string(const std::string_view s) {
    if (s == "None") return page_mode_t::None;
    if (s == "FullScreen") return page_mode_t::FullScreen;
    if (s == "UseOutlines") return page_mode_t::UseOutlines;
    if (s == "UseThumbs") return page_mode_t::UseThumbs;
    if (s == "UseCustomTags") return page_mode_t::UseCustomTags;
    if (s == "UseLayers") return page_mode_t::UseLayers;
    if (s == "UseAttatchs") return page_mode_t::UseAttatchs;
    if (s == "UseBookmarks") return page_mode_t::UseBookmarks;
    return std::nullopt;
  }
};

enum class page_layout_t { OnePage, OneColumn, TwoPageL, TwoColumnL, TwoPageR, TwoColumnR };
template<>
struct enum_converter<page_layout_t> {
  static std::string to_string(const page_layout_t e) {
    switch (e) {
      case page_layout_t::OnePage: return "OnePage";
      case page_layout_t::OneColumn: return "OneColumn";
      case page_layout_t::TwoPageL: return "TwoPageL";
      case page_layout_t::TwoColumnL: return "TwoColumnL";
      case page_layout_t::TwoPageR: return "TwoPageR";
      case page_layout_t::TwoColumnR: return "TwoColumnR";
    }
    return "";
  }
  static std::optional<page_layout_t> from_string(const std::string_view s) {
    if (s == "OnePage") return page_layout_t::OnePage;
    if (s == "OneColumn") return page_layout_t::OneColumn;
    if (s == "TwoPageL") return page_layout_t::TwoPageL;
    if (s == "TwoColumnL") return page_layout_t::TwoColumnL;
    if (s == "TwoPageR") return page_layout_t::TwoPageR;
    if (s == "TwoColumnR") return page_layout_t::TwoColumnR;
    return std::nullopt;
  }
};

enum class tab_display_t { DocTitle, FileName };
template<>
struct enum_converter<tab_display_t> {
  static std::string to_string(const tab_display_t e) {
    switch (e) {
      case tab_display_t::DocTitle: return "DocTitle";
      case tab_display_t::FileName: return "FileName";
    }
    return "";
  }
  static std::optional<tab_display_t> from_string(const std::string_view s) {
    if (s == "DocTitle") return tab_display_t::DocTitle;
    if (s == "FileName") return tab_display_t::FileName;
    return std::nullopt;
  }
};

enum class zoom_mode_t { Default, FitHeight, FitWidth, FitRect };
template<>
struct enum_converter<zoom_mode_t> {
  static std::string to_string(const zoom_mode_t e) {
    switch (e) {
      case zoom_mode_t::Default: return "Default";
      case zoom_mode_t::FitHeight: return "FitHeight";
      case zoom_mode_t::FitWidth: return "FitWidth";
      case zoom_mode_t::FitRect: return "FitRect";
    }
    return "";
  }
  static std::optional<zoom_mode_t> from_string(const std::string_view s) {
    if (s == "Default") return zoom_mode_t::Default;
    if (s == "FitHeight") return zoom_mode_t::FitHeight;
    if (s == "FitWidth") return zoom_mode_t::FitWidth;
    if (s == "FitRect") return zoom_mode_t::FitRect;
    return std::nullopt;
  }
};

struct v_preferences_t {
  std::optional<enum_string_t<page_mode_t> > page_mode_;
  std::optional<enum_string_t<page_layout_t> > page_layout_;
  std::optional<enum_string_t<tab_display_t> > tab_display_;
  std::optional<st_bool> hide_toolbar_;
  std::optional<st_bool> hide_menubar_;
  std::optional<st_bool> hide_window_ui_;
  std::optional<enum_string_t<zoom_mode_t> > zoom_mode_;
  std::optional<st_double> zoom_;
};

REFLECT_STRUCT(
  ofd_namespace"VPreferences",
  v_preferences_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"PageMode", &v_preferences_t::page_mode_),
    REFLECT_MEMBER(ofd_namespace"PageLayout", &v_preferences_t::page_layout_),
    REFLECT_MEMBER(ofd_namespace"TabDisplay", &v_preferences_t::tab_display_),
    REFLECT_MEMBER(ofd_namespace"HideToolbar", &v_preferences_t::hide_toolbar_),
    REFLECT_MEMBER(ofd_namespace"HideMenubar", &v_preferences_t::hide_menubar_),
    REFLECT_MEMBER(ofd_namespace"HideWindowUI", &v_preferences_t::hide_window_ui_),
    REFLECT_MEMBER(ofd_namespace"ZoomMode", &v_preferences_t::zoom_mode_),
    REFLECT_MEMBER(ofd_namespace"Zoom", &v_preferences_t::zoom_)
  )
)
} // tmpofd
