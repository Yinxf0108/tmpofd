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
#include "tmpofd/core/struct/common/variant_type.h"

namespace tmpofd {
template<is_st_bool T, is_st_string V>
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

template<is_st_number T, is_st_string V>
constexpr void parse_xml_value(T &ins, const V value) {
  if constexpr (is_floating_t<T>) {
    ins = value;
  } else {
    if (const auto result = std::from_chars(value.data(), value.data() + value.size(), ins); std::errc() != result.ec)
      throw std::runtime_error("Expected number value, but got '" + std::string{value} + "'");
  }
}

template<is_string_container T, is_st_string V>
constexpr void parse_xml_value(T &ins, const V value) {
  ins = value;
}

template<is_time T, is_st_string V>
constexpr void parse_xml_value(T &ins, const V value) {
  if constexpr (is_st_date<T>) {
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
  } else if constexpr (is_st_date_time<T>) {
    constexpr std::array<std::string_view, 2> formats = {
      "%Y-%m-%dT%H:%M:%S",
      "%Y-%m-%d %H:%M:%S",
    };

    for (const auto &fmt : formats) {
      std::stringstream ss{std::string{value}};
      std::tm tm = {};
      ss >> std::get_time(&tm, fmt.data());

      if (!ss.fail() && ss.eof()) {
        if (const auto ymd = std::chrono::year{tm.tm_year + 1900} / (tm.tm_mon + 1) / tm.tm_mday; ymd.ok()) {
          ins = std::chrono::sys_days(ymd)
              + std::chrono::hours{tm.tm_hour}
              + std::chrono::minutes{tm.tm_min}
              + std::chrono::seconds{tm.tm_sec};
          return;
        }
      }
    }
  } else {
    static_assert(always_false_v<T>, "Unknown time type");
  }

  throw std::runtime_error("Expected date/time value, but got '" + std::string{value} + "'");
}

template<is_id T, is_st_string V>
constexpr void parse_xml_value(T &ins, const V value) {
  ins = value;
}

template<is_spliting_string T, is_st_string V>
constexpr void parse_xml_value(T &ins, const V value) {
  ins.from_string(value);
}

template<is_optional T, is_st_string V>
constexpr void parse_xml_value(T &ins, const V value) {
  ins.emplace();
  parse_xml_value(*ins, value);
}

template<is_reflectable T, typename Pos>
constexpr void parse_xml_attr(T &ins, Pos &&pos, Pos &&end) {
  auto reflected = get_reflected(ins);

  while (pos < end) {
    skip_spaces_and_newline(std::forward<Pos>(pos), std::forward<Pos>(end));

    if ('>' == *pos || '/' == *pos)
      return;

    auto key = get_key<'='>(std::forward<Pos>(pos), std::forward<Pos>(end));
    skip_to<'='>(std::forward<Pos>(pos), std::forward<Pos>(end));
    ++pos;

    skip_spaces_and_newline(std::forward<Pos>(pos), std::forward<Pos>(end));

    auto value_begin = ++pos;
    skip_to<'"', '\''>(std::forward<Pos>(pos), std::forward<Pos>(end));
    auto value_end = pos;

    reflected.attr(
      key,
      [&](auto &&attr) {
        if (key == attr.name_)
          parse_xml_value(attr.invoke(ins), get_value(value_begin, value_end));
      }
    );

    ++pos;
  }
}

template<is_st_string_view N, is_base_type T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  skip_to<'>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  if ('/' == *(pos - 1)) {
    ++pos;
    return;
  }

  auto value_begin = ++pos;
  skip_to<'<'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  while (pos < end && '!' == *(pos + 1)) {
    ++pos;

    skip_comment(std::forward<Pos>(pos), std::forward<Pos>(end));
    skip_cdata(std::forward<Pos>(pos), std::forward<Pos>(end));

    skip_to<'<'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  }
  auto value_end = pos;

  parse_xml_value(ins, get_value(value_begin, value_end));

  matched_close(name, std::forward<Pos>(pos), std::forward<Pos>(end));
}

template<is_st_string_view N, is_variant T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  [&]<typename... VT>(std::variant<VT...> *) {
    bool parsed = false;

    ([&] {
      if (parsed) {
        return;
      }

      if (name == variant_type_name<VT>) {
        auto &member = ins.template emplace<VT>();
        parse_xml_node(name, member, std::forward<Pos>(pos), std::forward<Pos>(end));
        parsed = true;
      }
    }(), ...);
  }(static_cast<T *>(nullptr));
}

template<is_st_string_view N, is_optional T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  ins.emplace();
  parse_xml_node(name, *ins, std::forward<Pos>(pos), std::forward<Pos>(end));
}

template<is_st_string_view N, is_unique_ptr T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  if (!ins)
    ins = std::make_unique<typename T::element_type>();

  parse_xml_node(name, *ins, std::forward<Pos>(pos), std::forward<Pos>(end));
}

template<is_st_string_view N, is_st_vector T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  parse_xml_node(name, ins.emplace_back(), std::forward<Pos>(pos), std::forward<Pos>(end));

  while (pos < end) {
    skip_spaces_and_newline(std::forward<Pos>(pos), std::forward<Pos>(end));

    matched_skip<'<'>(std::forward<Pos>(pos), std::forward<Pos>(end));
    if ('?' == *pos || '!' == *pos) {
      --pos;
      return;
    }

    const auto key_begin = pos;
    auto key = get_key<'>', ' '>(std::forward<Pos>(pos), std::forward<Pos>(end));

    if (name != key) {
      pos = key_begin - 1;
      return;
    }

    parse_xml_node(name, ins.emplace_back(), std::forward<Pos>(pos), std::forward<Pos>(end));
  }
}

template<is_st_string_view N, is_reflectable T, typename Pos>
constexpr void parse_xml_node(const N name, T &ins, Pos &&pos, Pos &&end) {
  auto reflected = get_reflected(ins);

  if constexpr (0 != reflected.attr_size())
    parse_xml_attr(ins, std::forward<Pos>(pos), std::forward<Pos>(end));

  if constexpr (is_leaf_node<std::decay_t<T> >) {
    parse_xml_node(name, ins.leaf_value, std::forward<Pos>(pos), std::forward<Pos>(end));
    return;
  }

  skip_to<'/', '>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  if ('/' == *pos && '>' == *(pos + 1)) {
    pos += 2;
    return;
  }

  ++pos;

  if constexpr (0 == reflected.node_size())
    return;

  matched_close(name, std::forward<Pos>(pos), std::forward<Pos>(end));

  auto key = get_key<'>', ' '>(std::forward<Pos>(pos), std::forward<Pos>(end));

  while (true) {
    bool found = false;

    reflected.node(
      key,
      [&](auto &&node) {
        if (key == node.name_) {
          parse_xml_node(key, node.invoke(ins), std::forward<Pos>(pos), std::forward<Pos>(end));

          found = true;
          return;
        }

        if (matched_close(name, std::forward<Pos>(pos), std::forward<Pos>(end))) {
          found = true;
          return;
        }

        key = get_key<'>', ' '>(std::forward<Pos>(pos), std::forward<Pos>(end));
      }
    );

    if (!found)
      skip_node(key, std::forward<Pos>(pos), std::forward<Pos>(end));

    if (matched_close(name, std::forward<Pos>(pos), std::forward<Pos>(end)))
      return;

    key = get_key<'>', ' '>(std::forward<Pos>(pos), std::forward<Pos>(end));
  }
}

template<is_st_bool T, is_st_string XML>
constexpr void generate_xml_value(T &ins, XML &xml) {
  xml += ins ? "true" : "false";
}

template<is_st_number T, is_st_string XML>
constexpr void generate_xml_value(T &ins, XML &xml) {
  if constexpr (is_floating_t<T>) {
    xml += ins.to_string();
  } else {
    xml += std::to_string(ins);
  }
}

template<is_string_container T, is_st_string XML>
constexpr void generate_xml_value(T &ins, XML &xml) {
  if constexpr (is_st_string<T>) {
    xml += ins;
  } else if constexpr (is_st_loc<T>) {
    xml += ins.string();
  } else if constexpr (is_enum_string<T>) {
    xml += ins.str();
  } else {
    static_assert(always_false_v<T>, "Unknown instance type");
  }
}

template<is_time T, is_st_string XML>
constexpr void generate_xml_value(T &ins, XML &xml) {
  xml += to_string(ins);
}

template<is_id T, is_st_string XML>
constexpr void generate_xml_value(T &ins, XML &xml) {
  xml += ins.to_string();
}

template<is_spliting_string T, is_st_string XML>
constexpr void generate_xml_value(T &ins, XML &xml) {
  xml += ins.to_string();
}

template<is_optional T, is_st_string XML>
constexpr void generate_xml_value(T &ins, XML &xml) {
  if (ins.has_value())
    generate_xml_value(*ins, xml);
}

template<is_reflectable T, is_st_string XML>
constexpr void generate_xml_attr(T &ins, XML &xml) {
  auto reflected = get_reflected(ins);

  reflected.each_attr(
    [&](auto &&attr) {
      if constexpr (is_optional<decltype(attr.invoke(ins))>) {
        if (!attr.invoke(ins).has_value())
          return;
      }

      xml += ' ';
      xml.append(attr.name_);
      xml += R"(=")";

      generate_xml_value(attr.invoke(ins), xml);

      xml += R"(")";
    }
  );
}

template<is_st_string_view N, is_base_type T, is_st_string XML>
constexpr void generate_xml_node(const N name, T &ins, const int depth, XML &xml) {
#ifdef PRETTY_SERIALIZE
  xml += new_line;

  for (auto i = 0; i < depth; ++i)
    xml += tab;
#endif

  xml += '<';
  xml.append(name);
  xml += '>';

  generate_xml_value(ins, xml);

  xml += "</";
  xml.append(name);
  xml += ">";
}

template<is_st_string_view N, is_variant T, is_st_string XML>
constexpr void generate_xml_node(const N name, T &ins, const int depth, XML &xml) {
  std::visit(
    [&]<typename VT>(VT &&member) {
      if (name == variant_type_name<std::decay_t<VT> >)
        generate_xml_node(name, member, depth, xml);
    },
    ins
  );
}

template<is_st_string_view N, is_optional T, is_st_string XML>
constexpr void generate_xml_node(const N name, T &ins, const int depth, XML &xml) {
  if (ins.has_value())
    generate_xml_node(name, *ins, depth, xml);
}

template<is_st_string_view N, is_unique_ptr T, is_st_string XML>
constexpr void generate_xml_node(const N name, T &ins, const int depth, XML &xml) {
  if (ins)
    generate_xml_node(name, *ins, depth, xml);
}

template<is_st_string_view N, is_st_vector T, is_st_string XML>
constexpr void generate_xml_node(const N name, T &ins, const int depth, XML &xml) {
  for (const auto &item : ins) {
    generate_xml_node(name, item, depth, xml);
  }
}

template<is_st_string_view N, is_reflectable T, is_st_string XML>
constexpr void generate_xml_node(const N name, T &ins, const int depth, XML &xml) {
#ifdef PRETTY_SERIALIZE
  xml += new_line;

  if (0 != depth)
    for (auto i = 0; i < depth; ++i)
      xml += tab;
#endif

  auto reflected = get_reflected(ins);

  xml += '<';
  xml.append(name);

  if constexpr (0 != reflected.attr_size()) {
    generate_xml_attr(ins, xml);
  }

  if constexpr (0 == reflected.node_size()) {
    xml += "/>";

    return;
  }

  xml += '>';

  if constexpr (is_leaf_node<std::decay_t<T> >) {
    generate_xml_value(ins.leaf_value, xml);
  } else {
    bool has_child = false;
    reflected.each_node(
      [&](auto &&node) {
        const auto &member = node.invoke(ins);

        if constexpr (is_optional<decltype(member)>) {
          if (!member.has_value())
            return;
        }

        if constexpr (is_vector<decltype(member)>) {
          if (member.empty())
            return;
        }

        has_child = true;
        generate_xml_node(node.name_, node.invoke(ins), depth + 1, xml);
      }
    );

    if (!has_child) {
      xml.pop_back();
      xml += "/>";
      return;
    }

#ifdef PRETTY_SERIALIZE
    xml += new_line;

    if (0 != depth)
      for (auto i = 0; i < depth; ++i)
        xml += tab;
#endif
  }

  xml += "</";
  xml.append(name);
  xml += ">";
}
} // tmpofd
