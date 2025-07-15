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

#include <cstring>

#define new_line "\n"
#define tab "    "

namespace tmpofd {
inline std::string to_string(const st_date &date) {
  std::stringstream ss;
  ss << date;

  return ss.str();
}

inline std::string to_string(const std::optional<st_date> &date) {
  return to_string(*date);
}

inline std::string to_string(const st_date_time &dt) {
  const auto seconds_tp = std::chrono::floor<std::chrono::seconds>(dt);
  return std::format("{:%Y-%m-%dT%H:%M:%S}", seconds_tp);
}

inline std::string to_string(const std::optional<st_date_time> &dt) {
  return to_string(*dt);
}

template<char... characters, typename Pos>
constexpr void matched_skip(Pos &&pos, Pos &&end) {
  if (static_cast<size_t>(std::distance(std::forward<Pos>(pos), std::forward<Pos>(end))) < sizeof...(characters))
    throw std::runtime_error(
      std::string("Unexpected end of buffer. Expected matched skip : ").append(std::to_string(sizeof...(characters)))
    );

  constexpr char expected[] = {characters...};
  for (size_t i = 0; i < sizeof...(characters); ++i) {
    if (*pos++ != expected[i])
      throw std::runtime_error(std::string("Expected matched skip : ") + std::string(expected, sizeof...(characters)));
  }
}

constexpr uint64_t MAGIC_BROADCAST = 0x0101010101010101ULL;
constexpr uint64_t MAGIC_HIGH_BITS = 0x8080808080808080ULL;

template<char target_char>
constexpr uint64_t has_char(const uint64_t chunk) {
  /// broadcast target character to 8 bytes
  constexpr auto target_broadcast = static_cast<uint64_t>(static_cast<uint8_t>(target_char)) * MAGIC_BROADCAST;

  /// calculate XOR of each byte and target character
  const auto xor_result = chunk ^ target_broadcast;

  /// detecting zero bytes using bit manipulation
  /// if a byte is 0 (i.e., a match), that location generates a specific bit pattern
  const auto ret = xor_result - MAGIC_BROADCAST & ~xor_result & MAGIC_HIGH_BITS;

  return ret;
}

template<char... characters, typename Pos>
constexpr void skip_to(Pos &&pos, Pos &&end) {
  static_assert(sizeof...(characters) > 0, "Least one character must be specified");
  static_assert(std::contiguous_iterator<std::decay_t<Pos> >, "Discontinuous memory");

  if (sizeof(uint64_t) <= std::distance(std::forward<Pos>(pos), std::forward<Pos>(end))) {
    for (; pos <= end - sizeof(uint64_t); pos += sizeof(uint64_t)) {
      uint64_t chunk;
      std::memcpy(&chunk, std::to_address(pos), sizeof(chunk));

      if (const auto test = (has_char<characters>(chunk) | ...); 0 != test) {
        pos += std::countr_zero(test) >> 3;
        return;
      }
    }
  }

  while (pos < end) {
    if (((*pos == characters) || ...))
      return;

    ++pos;
  }

  constexpr char expected[] = {characters...};
  throw std::runtime_error(std::string("Expected skip to : ") + std::string(expected, sizeof...(characters)));
}

template<typename Pos>
constexpr void skip_spaces_and_newline(Pos &&pos, Pos &&end) {
  static_assert(std::is_same_v<std::decay_t<decltype(*pos)>, char>, "Not character parameter");

  while (pos < end && static_cast<std::uint8_t>(*pos) < 33)
    ++pos;
}

template<typename Pos>
constexpr void skip_instructions(Pos &&pos, Pos &&end) {
  if ('<' != *(pos - 1) && '?' != *pos)
    return;

  /// <?xml version="1.0" encoding="UTF-8"?>
  ///   ^
  ++pos;

  while (true) {
    skip_to<'?'>(std::forward<Pos>(pos), std::forward<Pos>(end));
    ++pos;

    if (pos >= end - 1)
      throw std::runtime_error("Unterminated processing instruction");

    if ('>' == *pos) {
      ++pos;
      break;
    }

    ++pos;
  }
}

template<typename Pos>
constexpr void skip_comment(Pos &&pos, Pos &&end) {
  if ('<' != *(pos - 1) && '!' != *pos)
    return;

  /// <!-- This is a comment -->
  ///  ^
  if (pos >= end - 3 || '-' != *(pos + 1) || '-' != *(pos + 2))
    return;

  /// <!-- This is a comment -->
  ///     ^
  matched_skip<'!', '-', '-'>(std::forward<Pos>(pos), std::forward<Pos>(end));

  while (true) {
    /// <!-- This is a comment -->
    ///                        ^
    skip_to<'-'>(std::forward<Pos>(pos), std::forward<Pos>(end));

    /// <!-- This is a comment -->
    ///                         ^
    ++pos;

    if (pos >= end - 2)
      throw std::runtime_error("Unterminated comment");

    if ('-' == *pos && '>' == *(pos + 1)) {
      /// <!-- This is a comment -->
      ///                           ^
      pos += 2;
      return;
    }

    ++pos;
  }

  throw std::runtime_error("Unterminated comment");
}

template<typename Pos>
constexpr void skip_doctype(Pos &&pos, Pos &&end) {
  if ('<' != *(pos - 1) && '!' != *pos)
    return;

  /// <!DOCTYPE root [<SYSTEM "example.dtd">]>
  ///  ^
  if (pos >= end - 8
    || 'D' != *(pos + 1)
    || 'O' != *(pos + 2)
    || 'C' != *(pos + 3)
    || 'T' != *(pos + 4)
    || 'Y' != *(pos + 5)
    || 'P' != *(pos + 6)
    || 'E' != *(pos + 7)
  )
    return;

  /// <!DOCTYPE root [<SYSTEM "example.dtd">]>
  ///          ^
  matched_skip<'!', 'D', 'O', 'C', 'T', 'Y', 'P', 'E'>(std::forward<Pos>(pos), std::forward<Pos>(end));

  /// <!DOCTYPE root [<SYSTEM "example.dtd">]>
  ///                ^
  /// <!DOCTYPE root SYSTEM "example.dtd">
  ///                                    ^
  skip_to<'[', '>'>(std::forward<Pos>(pos), std::forward<Pos>(end));

  if ('[' == *pos) {
    /// <!DOCTYPE root [<SYSTEM "example.dtd">]>
    ///                                       ^
    skip_to<']'>(std::forward<Pos>(pos), std::forward<Pos>(end));
    skip_to<'>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  }

  /// <!DOCTYPE root [<SYSTEM "example.dtd">]>
  ///                                         ^
  if (pos < end && '>' == *pos)
    ++pos;
}

template<typename Pos>
constexpr void skip_cdata(Pos &&pos, Pos &&end) {
  if ('<' != *(pos - 1) && '!' != *pos)
    return;

  /// <![CDATA[This is a CDATA block.]]>
  ///  ^
  if (pos >= end - 8
    || '[' != *(pos + 1)
    || 'C' != *(pos + 2)
    || 'D' != *(pos + 3)
    || 'A' != *(pos + 4)
    || 'T' != *(pos + 5)
    || 'A' != *(pos + 6)
    || '[' != *(pos + 7)
  )
    return;

  /// <![CDATA[This is a CDATA block.]]>
  ///          ^
  matched_skip<'!', '[', 'C', 'D', 'A', 'T', 'A', '['>(std::forward<Pos>(pos), std::forward<Pos>(end));

  /// <![CDATA[This is a CDATA block.]]>
  ///                                 ^
  skip_to<']'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  matched_skip<']'>(std::forward<Pos>(pos), std::forward<Pos>(end));

  /// <![CDATA[This is a CDATA block.]]>
  ///                                  ^
  skip_to<']'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  matched_skip<']'>(std::forward<Pos>(pos), std::forward<Pos>(end));

  /// <![CDATA[This is a CDATA block.]]>
  ///                                   ^
  skip_to<'>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  matched_skip<'>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
}

template<typename Pos>
constexpr void skip_to_first_key(Pos &&pos, Pos &&end) {
  while (pos < end) {
    skip_spaces_and_newline(std::forward<Pos>(pos), std::forward<Pos>(end));
    matched_skip<'<'>(std::forward<Pos>(pos), std::forward<Pos>(end));

    if ('?' == *pos) {
      skip_instructions(std::forward<Pos>(pos), std::forward<Pos>(end));
    } else if ('!' == *pos) {
      skip_comment(std::forward<Pos>(pos), std::forward<Pos>(end));
      skip_doctype(std::forward<Pos>(pos), std::forward<Pos>(end));
    } else {
      break;
    }
  }
}

template<char... characters, typename Pos>
constexpr auto get_key(Pos &&pos, Pos &&end) {
  auto begin = pos;
  skip_to<characters...>(std::forward<Pos>(pos), std::forward<Pos>(end));

  while (pos > begin && static_cast<std::uint8_t>(*(pos - 1)) < 33) {
    --pos;
  }

  return std::string_view{&*begin, static_cast<size_t>(std::distance(begin, pos))};
}

template<typename Pos>
constexpr auto get_value(Pos &&value_begin, Pos &&value_end) {
  auto value = std::string{&*value_begin, static_cast<size_t>(std::distance(value_begin, value_end))};

  constexpr auto cdata_prefix = std::string_view{"<![CDATA["};
  if (const auto pos = value.find(cdata_prefix); std::string_view::npos != pos) {
    const auto start = pos + cdata_prefix.length();
    if (const auto end = value.find("]]>", start); std::string_view::npos != end)
      return value.substr(start, end - start);

    throw std::runtime_error("Unterminated CDATA");
  }

  if (std::string_view::npos == value.find("<!--"))
    return value;

  std::string result;
  result.reserve(value.length());

  size_t pos = 0;
  while (pos < value.length()) {
    const auto start = value.find("<!--", pos);

    if (std::string_view::npos == start) {
      result.append(value.substr(pos));
      break;
    }

    result.append(value.substr(pos, start - pos));

    const auto end = value.find("-->", start + 4);
    if (std::string_view::npos == end)
      throw std::runtime_error("Unterminated comment");

    pos = end + 3;
  }

  return result;
}

template<is_string_view N, typename Pos>
constexpr auto matched_close(const N name, Pos &&pos, Pos &&end) {
  while (pos < end) {
    skip_spaces_and_newline(std::forward<Pos>(pos), std::forward<Pos>(end));
    matched_skip<'<'>(std::forward<Pos>(pos), std::forward<Pos>(end));

    if ('/' == *pos) {
      ++pos;

      const auto key = get_key<'>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
      if (key != name)
        throw std::runtime_error(
          "Mismatched closing tag, expected " + std::string(name) + " but got " + std::string(key)
        );

      ++pos;
      return true;
    }

    if ('?' == *pos) {
      skip_instructions(std::forward<Pos>(pos), std::forward<Pos>(end));
      continue;
    }

    if ('!' == *pos) {
      skip_comment(std::forward<Pos>(pos), std::forward<Pos>(end));
      skip_doctype(std::forward<Pos>(pos), std::forward<Pos>(end));
      skip_cdata(std::forward<Pos>(pos), std::forward<Pos>(end));
      continue;
    }

    return false;
  }

  return false;
}

template<is_string_view N, typename Pos>
constexpr void skip_node(const N name, Pos &&pos, Pos &&end) {
  skip_to<'>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
  ++pos;

  /// name />
  ///        ^
  if ('/' == *(pos - 2))
    return;

  while (pos < end) {
    /// <name> ... </name>
    ///             ^
    skip_to<'<'>(std::forward<Pos>(pos), std::forward<Pos>(end));
    ++pos;

    /// <name> ... </name>
    ///              ^
    if ('/' == *pos)
      ++pos;

    /// <name> ... </name>
    ///                  ^
    const auto key = get_key<'>'>(std::forward<Pos>(pos), std::forward<Pos>(end));
    if (name == key) {
      ++pos;
      return;
    }

    ++pos;
    skip_spaces_and_newline(std::forward<Pos>(pos), std::forward<Pos>(end));
  }

  throw std::runtime_error("Unclosed tag: " + std::string(name));
}
} // tmpofd
