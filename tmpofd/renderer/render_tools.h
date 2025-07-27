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

#include "tmpofd/core/traits/struct_traits.h"

#include <algorithm>

namespace tmpofd {
template<std::floating_point T>
[[nodiscard]] constexpr T px_to_mm(const T px, const double dpi = 96.0) noexcept {
  return px / dpi * 25.4;
}

template<std::floating_point T>
[[nodiscard]] constexpr T mm_to_px(const T mm, const double dpi = 96.0) noexcept {
  return mm / 25.4 * dpi;
}

inline st_box<st_double> intersect_boxes(const st_box<st_double> &box1, const st_box<st_double> &box2) {
  const auto x1 = std::max(box1.x_, box2.x_);
  const auto y1 = std::max(box1.y_, box2.y_);

  const auto box1_x2 = box1.x_ + box1.width_;
  const auto box1_y2 = box1.y_ + box1.height_;
  const auto box2_x2 = box2.x_ + box2.width_;
  const auto box2_y2 = box2.y_ + box2.height_;

  const auto x2 = std::min(box1_x2, box2_x2);
  const auto y2 = std::min(box1_y2, box2_y2);

  const auto width = x2 - x1;

  if (const auto height = y2 - y1; width > 0 && height > 0) {
    return {x1, y1, width, height};
  }
  return {};
}

inline auto calculate_render_area(const page_area_t &area) {
  auto render_area = area.physical_box_;

  if (area.application_box_) {
    render_area = intersect_boxes(render_area, *area.application_box_);
  }

  if (area.content_box_) {
    render_area = intersect_boxes(render_area, *area.content_box_);
  }

  /// ignore bleed box when render page

  return render_area;
}
} // tmpofd
