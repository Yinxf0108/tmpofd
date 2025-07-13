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

#include "tmpofd/core/serialization/serialization.h"
#include "tmpofd/core/struct/ofd/ofd.h"
#include "tmpofd/core/struct/common/simple_type.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <cassert>

using namespace tmpofd;

template<typename T>
T test_case(const std::string_view &name) {
  std::cout << "test case : " << name << std::endl;

  T entry{};

  try {
    if (const auto file_path = std::filesystem::current_path() / name; std::filesystem::exists(file_path)) {
      if (auto file = std::ifstream(file_path, std::ios::in | std::ios::binary)) {
        std::string content;
        content.assign(std::istreambuf_iterator(file), std::istreambuf_iterator<char>());

        from_xml(entry, std::string_view(content));
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "serialization error : " << e.what() << std::endl;
  }

  return entry;
}

int main() {
  const auto &[version_, doc_type_, doc_bodies_] = test_case<ofd_t>("ofd/baseline.xml");

  assert(version_ == "1.0");
  assert(doc_type_ == "OFD");
  assert(doc_type_ == doc_type_t::OFD);

  assert(doc_bodies_.size() == 1);
  if (!doc_bodies_.empty()) {
    const auto &[doc_info_, doc_root_, versions_, signatures_] = doc_bodies_[0];

    const auto &[
      doc_id_,
      title_,
      author_,
      subject_,
      abstract_,
      creation_date_,
      mod_date_,
      doc_usage_,
      cover_,
      keywords_,
      creator_,
      creator_version_,
      custom_datas_
    ] = doc_info_;
    assert(doc_id_ == "E9B52616-9506-0C9B-5C89-3458A9DD7181");
    assert(title_ == "OFD Template 1");
    assert(author_ == "Yinxf 1");
    assert(subject_ == "template 1");

    auto l = abstract_->length();
    assert(abstract_ == "its a OFD entry template 1");
    assert(to_string(creation_date_) == "2024-04-16");
    assert(to_string(mod_date_) == "2024-04-17");
    assert(doc_usage_ == "Normal");
    assert(cover_ == "Doc_0/res/cover.png");
    const auto &[keyword_] = *keywords_;
    assert(keyword_.size() == 2);
    assert(keyword_[0] == "OFD entry 1");
    assert(keyword_[1] == "template 1");
    assert(creator_ == "tmpofd 1");
    assert(creator_version_ == "0.1.0");
    const auto &[custom_data_] = *custom_datas_;
    assert(custom_data_[0].name_ == "Custom1");
    assert(custom_data_[0].leaf_value_ == "custom1 value 1");
    assert(custom_data_[1].name_ == "Custom2");
    assert(custom_data_[1].leaf_value_ == "custom2 value 2");

    assert(doc_root_ == "Doc_0/Document.xml");

    const auto &[version_] = *versions_;
    assert(version_.size() == 2);
    const auto &[id1, index1, current1, base_loc1] = version_[0];
    assert(id1 == static_cast<st_id>(1));
    assert(index1 == 0);
    assert(current1 == false);
    assert(base_loc1 == "Doc_0/Versions/Version_0/DocVersion.xml");
    const auto &[id2, index2, current2, base_loc2] = version_[1];
    assert(id2 == static_cast<st_id>(2));
    assert(index2 == 1);
    assert(current2 == true);
    assert(base_loc2 == "Doc_0/Versions/Version_1/DocVersion.xml");

    assert(signatures_ == "Doc_0/Signs/Signatures.xml");
  }

  auto ofd = test_case<ofd_t>("ofd/doctype_entity.xml");
  ofd = test_case<ofd_t>("ofd/minimal_robustness.xml");
  ofd = test_case<ofd_t>("ofd/special_chars.xml");
  ofd = test_case<ofd_t>("ofd/syntax_edge_cases.xml");

  return 0;
}
