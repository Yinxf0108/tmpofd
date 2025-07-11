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

#include "tmpofd/core/serialization/character_utils.h"
#include "tmpofd/core/struct/ofd/ofd.h"

#include <array>

namespace tmpofd {
template<is_st_bool T, is_string_view V>
constexpr void parse_xml_value(T &ins, const V value) {
  if ((4 == value.size()
      && ('t' == value[0] || 'T' == value[0])
      && ('r' == value[1] || 'R' == value[1])
      && ('u' == value[2] || 'U' == value[2])
      && ('e' == value[3] || 'E' == value[3])
    )
    || "1" == value
  ) {
    ins = true;
  } else if (
    (5 == value.size()
      && ('f' == value[0] || 'F' == value[0])
      && ('a' == value[1] || 'A' == value[1])
      && ('l' == value[2] || 'L' == value[2])
      && ('s' == value[3] || 'S' == value[3])
      && ('e' == value[4] || 'E' == value[4])
    ) || "0" == value
  ) {
    ins = false;
  } else {
    throw std::runtime_error("Expected bool value (true, false, 1, 0), but got '" + std::string{value} + "'");
  }
}

template<is_st_number T, is_string_view V>
constexpr void parse_xml_value(T &ins, const V value) {
  if (auto result = std::from_chars(value.data(), value.data() + value.size(), ins);
    result.ec != std::errc()
  ) {
    throw std::runtime_error("Expected number value, but got '" + std::string{value} + "'");
  }
}

template<can_passed_via_string_view T, is_string_view V>
constexpr void parse_xml_value(T &ins, const V value) {
  ins = value;
}

template<is_time T, is_string_view V>
constexpr void parse_xml_value(T &ins, const V value) {
  if constexpr (std::is_same_v<T, st_date>) {
    if (10 == value.length() && '-' == value[4] && '-' == value[7]) {
      int y{}, m{}, d{};

      auto res_y = std::from_chars(value.data(), value.data() + 4, y);
      auto res_m = std::from_chars(value.data() + 5, value.data() + 7, m);

      if (auto res_d = std::from_chars(value.data() + 8, value.data() + 10, d);
        std::errc{} == res_y.ec && std::errc{} == res_m.ec && std::errc{} == res_d.ec
      ) {
        ins = std::chrono::year_month_day{
          std::chrono::year{y},
          std::chrono::month{static_cast<unsigned>(m)},
          std::chrono::day{static_cast<unsigned>(d)}
        };

        return;
      }
    }
  } else if constexpr (std::is_same_v<T, st_date_time>) {
    constexpr std::array<std::string_view, 2> formats = {
      "%Y-%m-%dT%H:%M:%S",
      "%Y-%m-%d %H:%M:%S",
    };

    for (const auto &fmt : formats) {
      std::stringstream ss{std::string{value}};
      std::tm tm = {};
      ss >> std::get_time(&tm, fmt.data());

      if (!ss.fail() && ss.eof()) {
        const auto time_point = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        ins = time_point;
        return;
      }
    }
  } else {
    static_assert(always_false_v<T>, "Unknown time type");
  }

  throw std::runtime_error("Expected date/time value, but got '" + std::string{value} + "'");
}

template<is_id T, is_string_view V>
constexpr void parse_xml_value(T &ins, const V value) {
  std::uint64_t id = 0;
  if (auto result = std::from_chars(value.data(), value.data() + value.size(), id);
    result.ec != std::errc()
  ) {
    throw std::runtime_error("Expected ID value (unsigned integer), but got '" + std::string{value} + "'");
  }

  ins = id;
}

template<has_from_string T, is_string_view V>
constexpr void parse_xml_value(T &ins, const V value) {
  ins.from_string(value);
}

template<is_reflectable T, typename Pos>
constexpr void parse_xml_attr(T &ins, Pos &&pos, Pos &&end) {
  auto reflected = get_reflected(ins);

  while (pos < end) {
    skip_spaces_and_newline(pos, end);

    if ('>' == *pos || '/' == *pos)
      return;

    auto key = get_key<'='>(pos, end);
    skip_to<'='>(pos, end);
    ++pos;

    skip_spaces_and_newline(pos, end);

    auto value_begin = ++pos;
    skip_to<'"', '\''>(pos, end);
    auto value_end = pos;

    reflected.attr(
      key,
      [&](auto &&attr) {
        if (key == attr.name_) {
          /// TODO: value = try_to_get_cdata
          auto value = std::string_view{&*value_begin, static_cast<size_t>(std::distance(value_begin, pos))};
          parse_xml_value(attr.invoke(ins), value);
        }
      }
    );

    ++pos;
  }
}

template<is_string_view N, is_st_vector T, typename Pos>
constexpr void parse_xml_node(N name, T &ins, Pos &&pos, Pos &&end);
template<is_string_view N, is_reflectable T, typename Pos>
constexpr void parse_xml_node(N name, T &ins, Pos &&pos, Pos &&end);

template<is_string_view N, is_base_type T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  skip_to<'>'>(pos, end);
  if ('/' == *(pos - 1)) {
    ++pos;
    return;
  }

  auto value_begin = ++pos;

  skip_to<'<'>(pos, end);

  /// TODO: value = try_to_get_cdata
  auto value = std::string_view{&*value_begin, static_cast<size_t>(std::distance(value_begin, pos))};
  parse_xml_value(ins, value);

  matched_close(name, pos, end);
}

template<is_string_view N, is_st_vector T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  parse_xml_node(name, ins.emplace_back(), pos, end);

  while (pos < end) {
    skip_spaces_and_newline(pos, end);

    matched_skip<'<'>(pos, end);
    if ('?' == *pos || '!' == *pos) {
      --pos;
      return;
    }

    const auto key_begin = pos;
    auto key = get_key<'>', ' '>(pos, end);

    if (name != key) {
      pos = key_begin - 1;
      return;
    }

    parse_xml_node(name, ins.emplace_back(), pos, end);
  }
}

template<is_string_view N, is_reflectable T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  auto reflected = get_reflected(ins);

  if constexpr (0 != reflected.attr_size()) {
    parse_xml_attr(ins, pos, end);

    if constexpr (is_leaf_node<std::decay_t<T> >) {
      parse_xml_node(name, ins.leaf_value, pos, end);
      return;
    }
  }

  skip_to<'>'>(pos, end);
  ++pos;

  if constexpr (0 == reflected.node_size())
    return;

  matched_close(name, pos, end);

  auto key = get_key<'>', ' '>(pos, end);

  while (true) {
    bool found = false;

    reflected.node(
      key,
      [&](auto &&node) {
        if (key == node.name_) {
          parse_xml_node(key, node.invoke(ins), pos, end);
          found = true;
          return;
        }

        if (matched_close(name, pos, end)) {
          found = true;
          return;
        }

        key = get_key<'>', ' '>(pos, end);
      }
    );

    if (!found)
      skip_node(key, pos, end);

    if (matched_close(name, pos, end))
      return;

    key = get_key<'>', ' '>(pos, end);
  }
}
} // tmpofd
