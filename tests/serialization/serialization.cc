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
#include "tmpofd/core/struct/document/document.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <cassert>

using namespace tmpofd;

template<typename T>
T deserialize(const std::string_view &name) {
  std::cout << "deserialize : " << name << std::endl;

  T entry{};

  try {
    if (const auto file_path = std::filesystem::current_path() / name; std::filesystem::exists(file_path)) {
      if (auto file = std::ifstream(file_path, std::ios::in | std::ios::binary)) {
        std::string content;
        content.assign(std::istreambuf_iterator(file), std::istreambuf_iterator<char>());

        from_xml(entry, std::string_view{content});
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "deserialize error : " << e.what() << std::endl;
  }

  return entry;
}

template<typename T>
void serialize(const T &entry, const std::string_view &name) {
  std::cout << "serialize : " << name << std::endl;

  try {
    if (const auto file_path = std::filesystem::current_path() / name; std::filesystem::exists(file_path)) {
      if (auto file = std::ifstream(file_path, std::ios::in | std::ios::binary)) {
        std::string content;
        content.assign(std::istreambuf_iterator(file), std::istreambuf_iterator<char>());

        auto xml = to_xml(entry);
        std::cout << xml << std::endl;

        auto pos = content.find("\r\n");
        while (std::string::npos != pos) {
          content.replace(pos, 2, new_line);
          pos = content.find("\r\n");
        }

        pos = xml.find("\r\n");
        while (std::string::npos != pos) {
          xml.replace(pos, 2, new_line);
          pos = xml.find("\r\n");
        }

        assert(xml == content);
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "serialize error : " << e.what() << std::endl;
  }
}

void test_ofd() {
  auto ofd = deserialize<ofd_t>("ofd/baseline.xml");

  const auto &[namespace_, version_, doc_type_, doc_body_] = ofd;

  assert(namespace_ == "http://www.ofdspec.org/2016");
  assert(version_ == "1.0");
  assert(doc_type_ == "OFD");
  assert(doc_type_ == doc_type_t::OFD);

  assert(doc_body_.size() == 1);
  if (!doc_body_.empty()) {
    const auto &[doc_info_, doc_root_, versions_, signatures_] = doc_body_[0];

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
    assert(id1 == 1);
    assert(index1 == 0);
    assert(current1 == false);
    assert(base_loc1 == "Doc_0/Versions/Version_0/DocVersion.xml");
    const auto &[id2, index2, current2, base_loc2] = version_[1];
    assert(id2 == 2);
    assert(index2 == 1);
    assert(current2 == true);
    assert(base_loc2 == "Doc_0/Versions/Version_1/DocVersion.xml");

    assert(signatures_ == "Doc_0/Signs/Signatures.xml");
  }

  serialize(ofd, "ofd/baseline.xml");

  ofd = deserialize<ofd_t>("ofd/doctype_entity.xml");
  ofd = deserialize<ofd_t>("ofd/minimal_robustness.xml");
  ofd = deserialize<ofd_t>("ofd/special_chars.xml");
  ofd = deserialize<ofd_t>("ofd/syntax_edge_cases.xml");
}

void test_document() {
  auto document = deserialize<document_t>("document/baseline.xml");

  const auto &[
    max_unit_id_,
    page_area_,
    public_res_,
    document_res_,
    template_page_,
    default_cs_
  ] = document.common_data_;
  assert(max_unit_id_ == 100);
  assert(page_area_.physical_box_.to_string() == "0 0 210 297");
  assert(page_area_.application_box_->to_string() == "0 0 210 297");
  assert(page_area_.content_box_->to_string() == "10 10 200 287");
  assert(page_area_.bleed_box_->to_string() == "5 5 205 292");

  assert(public_res_.size() == 2);
  assert(public_res_[0] == "/Doc_0/PublicRes.xml");
  assert(public_res_[1] == "/Doc_0/PublicRes_2.xml");

  assert(document_res_.size() == 2);
  assert(document_res_[0] == "/Doc_0/DocumentRes.xml");
  assert(document_res_[1] == "/Doc_0/DocumentRes_2.xml");

  assert(template_page_.size() == 2);
  assert(template_page_[0].id_ == 1);
  assert(*template_page_[0].name_ == "Tpl_A");
  assert(*template_page_[0].z_order_ == z_order_t::Background);
  assert(template_page_[0].base_loc_ == "/Doc_0/Tpls/Tpl_1.xml");
  assert(template_page_[1].id_ == "2");
  assert(*template_page_[1].name_ == "Tpl_B");
  assert(*template_page_[1].z_order_ == z_order_t::Foreground);
  assert(template_page_[1].base_loc_ == "/Doc_0/Tpls/Tpl_2.xml");

  assert(default_cs_ == 1);

  const auto &[page_] = document.pages_;
  assert(page_.size() == 2);
  assert(page_[0].id_ == 3);
  assert(page_[0].base_loc_ == "/Doc_0/Pages/Page_0.xml");
  assert(page_[1].id_ == 4);
  assert(page_[1].base_loc_ == "/Doc_0/Pages/Page_1.xml");

  assert(document.outlines_.has_value());
  const auto &[outline_elem_0] = *document.outlines_;
  assert(outline_elem_0.size() == 2);

  const auto &[title_0, count_0, expanded_0, actions_0, outline_elem_0_0] = outline_elem_0[0];
  assert(title_0 == "第一章");
  assert(count_0.has_value() && count_0 == 1);
  assert(expanded_0.has_value() && expanded_0 == true);
  assert(actions_0.has_value() && actions_0->action_.size() == 1);
  const auto &action_0 = actions_0->action_[0];
  assert(action_0.event_ == action_event_t::DO);
  const auto goto_0 = std::get_if<goto_t>(&action_0.ops_);
  assert(goto_0 != nullptr);
  const auto dest_0 = std::get_if<dest_t>(&goto_0->ops_);
  assert(dest_0 != nullptr);
  assert(dest_0->type_ == dest_type_t::Fit);
  assert(dest_0->page_id_ == 3);
  assert(!dest_0->left_.has_value());
  assert(!dest_0->top_.has_value());
  assert(!dest_0->right_.has_value());
  assert(!dest_0->bottom_.has_value());
  assert(!dest_0->zoom_.has_value());
  assert(outline_elem_0_0.size() == 1);

  const auto &[title_0_0, count_0_0, expanded_0_0, actions_0_0, outline_elem_0_0_0] = *outline_elem_0_0[0];
  assert(title_0_0 == "1.1节");
  assert(count_0_0.has_value() && count_0_0 == 1);
  assert(expanded_0_0.has_value() && expanded_0_0 == false);
  assert(actions_0_0.has_value() && actions_0_0->action_.size() == 1);
  const auto &action_0_0 = actions_0_0->action_[0];
  assert(action_0_0.event_ == action_event_t::CLICK);
  const auto goto_0_0 = std::get_if<goto_t>(&action_0_0.ops_);
  assert(goto_0_0 != nullptr);
  const auto dest_0_0 = std::get_if<dest_t>(&goto_0_0->ops_);
  assert(dest_0_0 != nullptr);
  assert(dest_0_0->type_ == dest_type_t::FitH);
  assert(dest_0_0->page_id_ == 3);
  assert(!dest_0_0->left_.has_value());
  assert(dest_0_0->top_.has_value() && dest_0_0->top_ == "200");
  assert(!dest_0_0->right_.has_value());
  assert(!dest_0_0->bottom_.has_value());
  assert(!dest_0_0->zoom_.has_value());
  assert(outline_elem_0_0_0.size() == 1);

  const auto &[title_0_0_0, count_0_0_0, expanded_0_0_0, actions_0_0_0, outline_elem_0_0_0_0] = *outline_elem_0_0_0[0];
  assert(title_0_0_0 == "1.1.1 小节");
  assert(!count_0_0_0.has_value());
  assert(!expanded_0_0_0.has_value());
  assert(actions_0_0_0.has_value() && actions_0_0_0->action_.size() == 1);
  const auto &action_0_0_0 = actions_0_0_0->action_[0];
  assert(action_0_0_0.event_ == action_event_t::CLICK);
  const auto goto_0_0_0 = std::get_if<goto_t>(&action_0_0_0.ops_);
  assert(goto_0_0_0 != nullptr);
  const auto dest_0_0_0 = std::get_if<dest_t>(&goto_0_0_0->ops_);
  assert(dest_0_0_0 != nullptr);
  assert(dest_0_0_0->type_ == dest_type_t::FitV);
  assert(dest_0_0_0->page_id_ == 3);
  assert(dest_0_0_0->left_.has_value() && dest_0_0_0->left_ == 50.1);
  assert(!dest_0_0_0->top_.has_value());
  assert(!dest_0_0_0->right_.has_value());
  assert(!dest_0_0_0->bottom_.has_value());
  assert(!dest_0_0_0->zoom_.has_value());
  assert(outline_elem_0_0_0_0.empty());

  const auto &[title_1, count_1, expanded_1, actions_1, outline_elem_1_0] = outline_elem_0[1];
  assert(title_1 == "第二章");
  assert(!count_1.has_value());
  assert(!expanded_1.has_value());
  assert(!actions_1.has_value());
  assert(outline_elem_1_0.size() == 2);

  const auto &[title_1_0, count_1_0, expanded_1_0, actions_1_0, outline_elem_1_0_0] = *outline_elem_1_0[0];
  assert(title_1_0 == "2.1节");
  assert(!count_1_0.has_value());
  assert(!expanded_1_0.has_value());
  assert(!actions_1_0.has_value());
  assert(outline_elem_1_0_0.empty());

  const auto &[title_1_1, count_1_1, expanded_1_1, actions_1_1, outline_elem_1_1_0] = *outline_elem_1_0[1];
  assert(title_1_1 == "2.2节");
  assert(!count_1_1.has_value());
  assert(!expanded_1_1.has_value());
  assert(!actions_1_1.has_value());
  assert(outline_elem_1_1_0.empty());

  assert(document.permissions_.has_value());
  const auto &permissions = *document.permissions_;
  assert(permissions.edit_.has_value() && permissions.edit_ == false);
  assert(permissions.annot_.has_value() && permissions.annot_ == true);
  assert(permissions.export_.has_value() && permissions.export_ == true);
  assert(permissions.signature_.has_value() && permissions.signature_ == false);
  assert(permissions.watermark_.has_value() && permissions.watermark_ == true);
  assert(permissions.print_screen_.has_value() && permissions.print_screen_ == false);
  assert(permissions.print_.has_value() && permissions.print_.has_value());
  assert(permissions.print_.has_value() && permissions.print_->printable_ == true);
  assert(permissions.print_->copies_.has_value() && permissions.print_->copies_ == 10);
  assert(permissions.valid_period_.has_value());
  assert(
    permissions.valid_period_->start_date_.has_value()
    && to_string(permissions.valid_period_->start_date_.value()) == "2025-01-01T00:00:00"
  );
  assert(
    permissions.valid_period_->end_date_.has_value()
    && to_string(permissions.valid_period_->end_date_.value()) == "2025-12-31T23:59:59"
  );

  assert(document.actions_.has_value());
  assert(document.actions_->action_.size() == 5);

  const auto &actions_t_0 = document.actions_->action_[0];
  assert(actions_t_0.event_ == action_event_t::DO);
  const auto actions_t_0_goto = std::get_if<goto_t>(&actions_t_0.ops_);
  assert(actions_t_0_goto != nullptr);
  const auto bookmark = std::get_if<_bookmark_t>(&actions_t_0_goto->ops_);
  assert(bookmark != nullptr);
  assert(bookmark->name_ == "Bookmark 1");

  const auto &actions_t_1 = document.actions_->action_[1];
  assert(actions_t_1.event_ == action_event_t::PO);
  const auto actions_t_1_uri = std::get_if<uri_t>(&actions_t_1.ops_);
  assert(actions_t_1_uri != nullptr);
  assert(actions_t_1_uri->uri_ == "/logout");
  assert(actions_t_1_uri->base_.has_value() && actions_t_1_uri->base_ == "https://github.com");
  assert(actions_t_1_uri->target_.has_value() && actions_t_1_uri->target_ == "_blank");

  const auto &actions_t_2 = document.actions_->action_[2];
  assert(actions_t_2.event_ == action_event_t::CLICK);
  const auto actions_t_2_goto_a = std::get_if<goto_a_t>(&actions_t_2.ops_);
  assert(actions_t_2_goto_a != nullptr);
  assert(actions_t_2_goto_a->attach_id_ == 7);
  assert(actions_t_2_goto_a->new_window_.has_value() &&actions_t_2_goto_a->new_window_ == false);

  const auto &actions_t_3 = document.actions_->action_[3];
  assert(actions_t_3.event_ == action_event_t::DO);
  const auto actions_t_3_sound = std::get_if<sound_t>(&actions_t_3.ops_);
  assert(actions_t_3_sound != nullptr);
  assert(actions_t_3_sound->resource_id_ == 4);
  assert(actions_t_3_sound->volume_.has_value() &&actions_t_3_sound->volume_ == 100);
  assert(actions_t_3_sound->repeat_.has_value() &&actions_t_3_sound->repeat_ == false);
  assert(actions_t_3_sound->synchronous_.has_value() &&actions_t_3_sound->synchronous_ == true);

  const auto &actions_t_4 = document.actions_->action_[4];
  assert(actions_t_4.event_ == action_event_t::PO);
  const auto actions_t_4_movie = std::get_if<movie_t>(&actions_t_4.ops_);
  assert(actions_t_4_movie != nullptr);
  assert(actions_t_4_movie->resource_id_ == 5);
  assert(actions_t_4_movie->operator_.has_value() && actions_t_4_movie->operator_ == movie_operator_t::Play);

  assert(document.v_preferences_.has_value());
  const auto &v_preferences = *document.v_preferences_;
  assert(v_preferences.page_mode_.has_value() && v_preferences.page_mode_ == page_mode_t::UseOutlines);
  assert(v_preferences.page_layout_.has_value() && v_preferences.page_layout_ == page_layout_t::TwoPageL);
  assert(v_preferences.tab_display_.has_value() && v_preferences.tab_display_ == tab_display_t::DocTitle);
  assert(v_preferences.hide_toolbar_.has_value() && v_preferences.hide_toolbar_ == false);
  assert(v_preferences.hide_menubar_.has_value() && v_preferences.hide_menubar_ == false);
  assert(v_preferences.hide_window_ui_.has_value() && v_preferences.hide_window_ui_ == false);
  assert(v_preferences.zoom_ops_.has_value());
  const auto zoom = std::get_if<enum_string_t<zoom_mode_t> >(&*v_preferences.zoom_ops_);
  assert(zoom != nullptr);
  assert(*zoom == zoom_mode_t::FitWidth);

  assert(document.bookmarks_.has_value());
  const auto &bookmarks = *document.bookmarks_;
  assert(bookmarks.bookmark_.size() == 2);

  assert(bookmarks.bookmark_[0].name_ == "Bookmark 1");
  assert(bookmarks.bookmark_[0].dest_.type_ == dest_type_t::FitH);
  assert(bookmarks.bookmark_[0].dest_.page_id_ == 3);
  assert(!bookmarks.bookmark_[0].dest_.left_.has_value());
  assert(bookmarks.bookmark_[0].dest_.top_.has_value() && bookmarks.bookmark_[0].dest_.top_ == 200.12);
  assert(bookmarks.bookmark_[0].dest_.top_.has_value() && bookmarks.bookmark_[0].dest_.top_ == "200.12");
  assert(!bookmarks.bookmark_[0].dest_.right_.has_value());
  assert(!bookmarks.bookmark_[0].dest_.bottom_.has_value());
  assert(!bookmarks.bookmark_[0].dest_.zoom_.has_value());

  assert(bookmarks.bookmark_[1].name_ == "Bookmark 2");
  assert(bookmarks.bookmark_[1].dest_.type_ == dest_type_t::FitR);
  assert(bookmarks.bookmark_[1].dest_.page_id_ == 4);
  assert(bookmarks.bookmark_[1].dest_.left_.has_value() && bookmarks.bookmark_[1].dest_.left_ == 10.123);
  assert(bookmarks.bookmark_[1].dest_.top_.has_value() && bookmarks.bookmark_[1].dest_.top_ == 10.123456);
  assert(bookmarks.bookmark_[1].dest_.right_.has_value() && bookmarks.bookmark_[1].dest_.right_ == 100.000000);
  assert(
    bookmarks.bookmark_[1].dest_.bottom_.has_value()
    && bookmarks.bookmark_[1].dest_.bottom_ == 100
    && bookmarks.bookmark_[1].dest_.bottom_ == 100.0
    && bookmarks.bookmark_[1].dest_.bottom_ != 100.1
  );
  assert(!bookmarks.bookmark_[1].dest_.zoom_.has_value());

  assert(document.annotations_ == "/Doc_0/Annotations.xml");
  assert(document.custom_tags_ == "/Doc_0/CustomTags.xml");
  assert(document.attachments_ == "/Doc_0/Attachments.xml");
  assert(document.extensions_ == "/Doc_0/Extensions.xml");

  serialize(document, "document/baseline.xml");
}

int main() {
  test_ofd();
  test_document();
  /// TODO: test_page();

  return 0;
}
