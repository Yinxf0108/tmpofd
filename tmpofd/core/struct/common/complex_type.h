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
#include "tmpofd/core/struct/common/variant_type.h"

namespace tmpofd {
struct page_area_t {
  st_box<st_double> physical_box_;
  std::optional<st_box<st_double> > application_box_;
  std::optional<st_box<st_double> > content_box_;
  std::optional<st_box<st_double> > bleed_box_;
};

REFLECT_STRUCT(
  ofd_namespace"PageArea",
  page_area_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"PhysicalBox", &page_area_t::physical_box_),
    REFLECT_MEMBER(ofd_namespace"ApplicationBox", &page_area_t::application_box_),
    REFLECT_MEMBER(ofd_namespace"ContentBox", &page_area_t::content_box_),
    REFLECT_MEMBER(ofd_namespace"BleedBox", &page_area_t::bleed_box_)
  )
)
struct move_t {
  st_pos<st_double> point1_;
};

REFLECT_STRUCT(
  ofd_namespace"Move",
  move_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Point1", &move_t::point1_)
  )
  REFLECT_NODE()
)

struct line_t {
  st_pos<st_double> point1_;
};

REFLECT_STRUCT(
  ofd_namespace"Line",
  line_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Point1", &line_t::point1_)
  )
  REFLECT_NODE()
)

struct quadratic_bezier_t {
  st_pos<st_double> point1_;
  st_pos<st_double> point2_;
};

REFLECT_STRUCT(
  ofd_namespace"QuadraticBezier",
  quadratic_bezier_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Point1", &quadratic_bezier_t::point1_),
    REFLECT_MEMBER("Point2", &quadratic_bezier_t::point2_)
  )
  REFLECT_NODE()
)

struct cubic_bezier_t {
  std::optional<st_pos<st_double> > point1_;
  std::optional<st_pos<st_double> > point2_;
  st_pos<st_double> point3_;
};

REFLECT_STRUCT(
  ofd_namespace"CubicBezier",
  cubic_bezier_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Point1", &cubic_bezier_t::point1_),
    REFLECT_MEMBER("Point2", &cubic_bezier_t::point2_),
    REFLECT_MEMBER("Point3", &cubic_bezier_t::point3_)
  )
  REFLECT_NODE()
)

struct arc_t {
  st_bool sweep_direction_{};
  st_bool large_arc_{};
  st_double rotation_angle_{};
  st_array<st_double> ellipse_size_;
  st_pos<st_double> end_point_;
};

REFLECT_STRUCT(
  ofd_namespace"Arc",
  arc_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("SweepDirection", &arc_t::sweep_direction_),
    REFLECT_MEMBER("LargeArc", &arc_t::large_arc_),
    REFLECT_MEMBER("RotationAngle", &arc_t::rotation_angle_),
    REFLECT_MEMBER("EllipseSize", &arc_t::ellipse_size_),
    REFLECT_MEMBER("EndPoint", &arc_t::end_point_)
  )
  REFLECT_NODE()
)

struct close_t {
  st_pos<st_double> leaf_value;
};

REFLECT_STRUCT(
  ofd_namespace"Close",
  close_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER("", &close_t::leaf_value)
  )
)

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(region_area_op_t, move_t, line_t, quadratic_bezier_t, cubic_bezier_t, arc_t, close_t),
  DEFINE_VARIANT_TYPE(move_t, ofd_namespace"Move")
  DEFINE_VARIANT_TYPE(line_t, ofd_namespace"Line")
  DEFINE_VARIANT_TYPE(quadratic_bezier_t, ofd_namespace"QuadraticBezier")
  DEFINE_VARIANT_TYPE(cubic_bezier_t, ofd_namespace"CubicBezier")
  DEFINE_VARIANT_TYPE(arc_t, ofd_namespace"Arc")
  DEFINE_VARIANT_TYPE(close_t, ofd_namespace"Close")
)

struct region_area_t {
  st_pos<st_double> start_;
  st_vector<region_area_op_t> ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Area",
  region_area_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Start", &region_area_t::start_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Move", &region_area_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Line", &region_area_t::ops_),
    REFLECT_MEMBER(ofd_namespace"QuadraticBezier", &region_area_t::ops_),
    REFLECT_MEMBER(ofd_namespace"CubicBezier", &region_area_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Arc", &region_area_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Close", &region_area_t::ops_)
  )
)

struct region_t {
  st_vector<region_area_t> area_;
};

REFLECT_STRUCT(
  ofd_namespace"Region",
  region_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Area", &region_t::area_)
  )
)

enum class dest_type_t { XYZ, Fit, FitH, FitV, FitR };
template<>
struct enum_converter<dest_type_t> {
  static std::string to_string(const dest_type_t e) {
    switch (e) {
      case dest_type_t::XYZ: return "XYZ";
      case dest_type_t::Fit: return "Fit";
      case dest_type_t::FitH: return "FitH";
      case dest_type_t::FitV: return "FitV";
      case dest_type_t::FitR: return "FitR";
    }
    return "";
  }
  static std::optional<dest_type_t> from_string(const std::string_view s) {
    if (s == "XYZ") return dest_type_t::XYZ;
    if (s == "Fit") return dest_type_t::Fit;
    if (s == "FitH") return dest_type_t::FitH;
    if (s == "FitV") return dest_type_t::FitV;
    if (s == "FitR") return dest_type_t::FitR;
    return std::nullopt;
  }
};

struct dest_t {
  enum_string_t<dest_type_t> type_;
  st_ref_id page_id_;
  std::optional<st_double> left_;
  std::optional<st_double> top_;
  std::optional<st_double> right_;
  std::optional<st_double> bottom_;
  std::optional<st_double> zoom_;
};

REFLECT_STRUCT(
  ofd_namespace"Dest",
  dest_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Type", &dest_t::type_),
    REFLECT_MEMBER("PageID", &dest_t::page_id_),
    REFLECT_MEMBER("Left", &dest_t::left_),
    REFLECT_MEMBER("Top", &dest_t::top_),
    REFLECT_MEMBER("Right", &dest_t::right_),
    REFLECT_MEMBER("Bottom", &dest_t::bottom_),
    REFLECT_MEMBER("Zoom", &dest_t::zoom_)
  )
  REFLECT_NODE()
)

struct _bookmark_t {
  st_string name_;
};

REFLECT_STRUCT(
  ofd_namespace"Bookmark",
  _bookmark_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Name", &_bookmark_t::name_)
  )
  REFLECT_NODE()
)

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(goto_op_t, dest_t, _bookmark_t),
  DEFINE_VARIANT_TYPE(dest_t, ofd_namespace"Dest")
  DEFINE_VARIANT_TYPE(_bookmark_t, ofd_namespace"Bookmark")
)

struct goto_t {
  goto_op_t ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Goto",
  goto_t,
  REFLECT_ATTR()
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Dest", &goto_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Bookmark", &goto_t::ops_)
  )
)

struct uri_t {
  st_string uri_;
  std::optional<st_string> base_;
  std::optional<st_string> target_;
};

REFLECT_STRUCT(
  ofd_namespace"URI",
  uri_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("URI", &uri_t::uri_),
    REFLECT_MEMBER("Base", &uri_t::base_),
    REFLECT_MEMBER("Target", &uri_t::target_)
  )
  REFLECT_NODE()
)

struct goto_a_t {
  st_ref_id attach_id_;
  std::optional<st_bool> new_window_;
};

REFLECT_STRUCT(
  ofd_namespace"GotoA",
  goto_a_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("AttachID", &goto_a_t::attach_id_),
    REFLECT_MEMBER("NewWindow", &goto_a_t::new_window_)
  )
  REFLECT_NODE()
)

struct sound_t {
  st_ref_id resource_id_;
  std::optional<st_int> volume_;
  std::optional<st_bool> repeat_;
  std::optional<st_bool> synchronous_;
};

REFLECT_STRUCT(
  ofd_namespace"Sound",
  sound_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ResourceID", &sound_t::resource_id_),
    REFLECT_MEMBER("Volume", &sound_t::volume_),
    REFLECT_MEMBER("Repeat", &sound_t::repeat_),
    REFLECT_MEMBER("Synchronous", &sound_t::synchronous_)
  )
  REFLECT_NODE()
)

enum class movie_operator_t { Play, Stop, Pause, Resume };
template<>
struct enum_converter<movie_operator_t> {
  static std::string to_string(const movie_operator_t e) {
    switch (e) {
      case movie_operator_t::Play: return "Play";
      case movie_operator_t::Stop: return "Stop";
      case movie_operator_t::Pause: return "Pause";
      case movie_operator_t::Resume: return "Resume";
    }
    return "";
  }
  static std::optional<movie_operator_t> from_string(const std::string_view s) {
    if (s == "Play") return movie_operator_t::Play;
    if (s == "Stop") return movie_operator_t::Stop;
    if (s == "Pause") return movie_operator_t::Pause;
    if (s == "Resume") return movie_operator_t::Resume;
    return std::nullopt;
  }
};

struct movie_t {
  st_ref_id resource_id_;
  std::optional<enum_string_t<movie_operator_t> > operator_;
};

REFLECT_STRUCT(
  ofd_namespace"Movie",
  movie_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("ResourceID", &movie_t::resource_id_),
    REFLECT_MEMBER("Operator", &movie_t::operator_)
  )
  REFLECT_NODE()
)

DEFINE_VARIANT(
  DEFINE_VARIANT_ALIAS(action_op_t, goto_t, uri_t, goto_a_t, sound_t, movie_t),
  DEFINE_VARIANT_TYPE(goto_t, ofd_namespace"Goto")
  DEFINE_VARIANT_TYPE(uri_t, ofd_namespace"URI")
  DEFINE_VARIANT_TYPE(goto_a_t, ofd_namespace"GotoA")
  DEFINE_VARIANT_TYPE(sound_t, ofd_namespace"Sound")
  DEFINE_VARIANT_TYPE(movie_t, ofd_namespace"Movie")
)

enum class action_event_t { DO, PO, CLICK };
template<>
struct enum_converter<action_event_t> {
  static std::string to_string(const action_event_t e) {
    switch (e) {
      case action_event_t::DO: return "DO";
      case action_event_t::PO: return "PO";
      case action_event_t::CLICK: return "CLICK";
    }
    return "";
  }
  static std::optional<action_event_t> from_string(const std::string_view s) {
    if (s == "DO") return action_event_t::DO;
    if (s == "PO") return action_event_t::PO;
    if (s == "CLICK") return action_event_t::CLICK;
    return std::nullopt;
  }
};

struct action_t {
  enum_string_t<action_event_t> event_;
  std::optional<region_t> region_;
  action_op_t ops_;
};

REFLECT_STRUCT(
  ofd_namespace"Action",
  action_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Event", &action_t::event_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Region", &action_t::region_),
    REFLECT_MEMBER(ofd_namespace"Goto", &action_t::ops_),
    REFLECT_MEMBER(ofd_namespace"URI", &action_t::ops_),
    REFLECT_MEMBER(ofd_namespace"GotoA", &action_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Sound", &action_t::ops_),
    REFLECT_MEMBER(ofd_namespace"Movie", &action_t::ops_)
  )
)

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

struct color_t;
struct segment_t {
  std::optional<st_double> position_;
  std::unique_ptr<color_t> color_;
};

REFLECT_STRUCT(
  ofd_namespace"Segment",
  segment_t,
  REFLECT_ATTR(
    REFLECT_MEMBER("Position", &segment_t::position_)
  )
  REFLECT_NODE(
    REFLECT_MEMBER(ofd_namespace"Color", &segment_t::color_)
  )
)
} // tmpofd
