/**
 * MIT License
 * 
 * Copyright (c) 2024 Yinxf
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#pragma once

#include "tmpofd/core/reflection/reflection.h"
#include "tmpofd/core/serialization/xml_tools.h"

namespace tmpofd {
template<is_reflectable T, is_string_view XML>
constexpr void from_xml(T &ins, const XML &xml) {
  auto pos = std::begin(xml);
  auto end = std::end(xml);

  skip_to_first_key(pos, end);

  auto key = get_key<'>', ' '>(pos, end);

  parse_xml_node(key, ins, pos, end);
}

template<is_reflectable T>
std::string to_xml(const T &ins) {
  auto reflected = get_reflected(ins);

  std::string xml;
  xml.reserve(4096);
  xml += R"(<?xml version="1.0" encoding="UTF-8"?>)";

  constexpr auto depth = 0;
  generate_xml_node(reflected.name(), ins, depth, xml);

  return xml;
}
} // tmpofd
