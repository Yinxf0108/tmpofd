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
#include "tmpofd/core/struct/page/page.h"
#include "tmpofd/core/struct/annotation/annotation.h"
#include "tmpofd/core/struct/annotations/annotations.h"
#include "tmpofd/core/struct/attachments/attachments.h"
#include "tmpofd/core/struct/custom_tags/custom_tags.h"
#include "tmpofd/core/struct/extensions/extensions.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <cassert>

#include "tmpofd/core/struct/res/res.h"

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

void test_page() {
  auto page = deserialize<page_t>("page/baseline.xml");

  assert(page.namespace_.has_value() && page.namespace_ == "http://www.ofdspec.org/2016");

  assert(page.templates_.size() == 2);
  const auto &tpl1 = page.templates_[0];
  assert(tpl1.template_id_ == 1);
  assert(tpl1.z_order_.has_value() && tpl1.z_order_ == "Background" && tpl1.z_order_ == z_order_t::Background);

  const auto &tpl2 = page.templates_[1];
  assert(tpl2.template_id_ == 2);
  assert(tpl2.z_order_.has_value() && tpl2.z_order_ == z_order_t::Foreground);

  assert(page.page_res_.size() == 2);
  assert(page.page_res_[0] == "/Res/Font.xml");
  assert(page.page_res_[1] == "/Res/Image.xml");

  assert(page.area_.has_value());
  const auto &area = *page.area_;
  assert(area.physical_box_.to_string() == "0 0 210 297");
  assert(area.physical_box_.x_ == 0.0);
  assert(area.physical_box_.y_ == 0.0);
  assert(area.physical_box_.width_ == 210.0);
  assert(area.physical_box_.height_ == 297.0);
  assert(area.application_box_.has_value() && area.application_box_->to_string() == "10 10 190 277");
  assert(area.content_box_.has_value() && area.content_box_->to_string() == "15 15 180 267");
  assert(area.bleed_box_.has_value() && area.bleed_box_->to_string() == "5 5 200 287");

  assert(page.content_.has_value());
  const auto &content = *page.content_;
  assert(content.layer_.size() == 2);

  const auto &layer1 = content.layer_[0];
  assert(layer1.id_ == 10);
  assert(layer1.type_.has_value() && layer1.type_ == layer_type_t::Body);
  assert(layer1.draw_param_.has_value() && layer1.draw_param_ == 3);

  assert(layer1.ops_.size() == 2);

  assert(std::holds_alternative<_text_t>(layer1.ops_[0]));
  const auto &text_obj = std::get<_text_t>(layer1.ops_[0]);
  assert(text_obj.id_ == 20);
  assert(text_obj.boundary_.to_string() == "20 20 100 40");
  assert(text_obj.name_.has_value() && text_obj.name_ == "TitleText");
  assert(text_obj.visible_.has_value() && text_obj.visible_);
  assert(text_obj.ctm_.has_value() && text_obj.ctm_->to_string() == "1 0 0 1 20 20");
  assert(text_obj.draw_param_.has_value() && text_obj.draw_param_ == 4);
  assert(text_obj.line_width_.has_value() && text_obj.line_width_ == 0.5);
  assert(text_obj.cap_.has_value() && text_obj.cap_ == cap_type_t::Square);
  assert(text_obj.join_.has_value() && text_obj.join_ == join_type_t::Round);
  assert(text_obj.miter_limit_.has_value() && text_obj.miter_limit_ == 3.0);
  assert(text_obj.dash_offset_.has_value() && text_obj.dash_offset_ == 1.0);
  assert(text_obj.dash_pattern_.has_value() && text_obj.dash_pattern_->to_string() == "2 1");
  assert(text_obj.alpha_.has_value() && text_obj.alpha_ == 200);
  assert(text_obj.font_ == 5);
  assert(text_obj.size_ == 12.0);
  assert(text_obj.stroke_.has_value() && text_obj.stroke_);
  assert(text_obj.fill_.has_value() && !*text_obj.fill_);
  assert(text_obj.h_scale_.has_value() && text_obj.h_scale_ == 1.2);
  assert(text_obj.read_direction_.has_value() && text_obj.read_direction_ == 90);
  assert(text_obj.char_direction_.has_value() && text_obj.char_direction_ == 90);
  assert(text_obj.weight_.has_value() && text_obj.weight_ == weight_t::_500);
  assert(text_obj.italic_.has_value() && text_obj.italic_);
  assert(text_obj.actions_.has_value() && text_obj.actions_->action_.size() == 2);
  const auto &actions_0 = text_obj.actions_->action_[0];
  assert(actions_0.event_ == action_event_t::CLICK);
  assert(actions_0.region_.has_value());
  const auto &region_0 = actions_0.region_;
  assert(region_0->area_.size() == 2);
  const auto &area_0 = region_0->area_[0];
  assert(area_0.start_.to_string() == "0 0");
  assert(area_0.ops_.size() == 4);
  const auto area_0_line0 = std::get_if<line_t>(&area_0.ops_[0]);
  assert(area_0_line0 != nullptr);
  assert(area_0_line0->point1_.to_string() == "80 0");
  const auto area_0_line1 = std::get_if<line_t>(&area_0.ops_[1]);
  assert(area_0_line1 != nullptr);
  assert(area_0_line1->point1_.to_string() == "80 20");
  const auto area_0_line2 = std::get_if<line_t>(&area_0.ops_[2]);
  assert(area_0_line2 != nullptr);
  assert(area_0_line2->point1_.to_string() == "0 20");
  const auto area_0_close = std::get_if<close_t>(&area_0.ops_[3]);
  assert(area_0_close != nullptr);
  assert(area_0_close->leaf_value_.to_string() == "0 0");
  const auto &area_1 = region_0->area_[1];
  assert(area_1.start_.to_string() == "10 10");
  const auto actions_0_goto = std::get_if<goto_t>(&actions_0.ops_);
  assert(actions_0_goto != nullptr);
  const auto dest_0 = std::get_if<dest_t>(&actions_0_goto->ops_);
  assert(dest_0 != nullptr);
  assert(dest_0->type_ == dest_type_t::FitR);
  assert(dest_0->page_id_ == 3);
  assert(dest_0->left_.has_value() && dest_0->left_ == 0);
  assert(dest_0->top_.has_value() && dest_0->top_ == 0);
  assert(dest_0->right_.has_value() && dest_0->right_ == 100);
  assert(dest_0->bottom_.has_value() && dest_0->bottom_ == 100);
  assert(dest_0->zoom_.has_value() && dest_0->zoom_ == 150.0);
  assert(text_obj.clips_.has_value());
  const clips_t &clips = *text_obj.clips_;
  assert(clips.clip_.size() == 2);
  const clip_t &clip1 = clips.clip_[0];
  const auto &area1 = clip1.area_;
  assert(area1.draw_param_.has_value());
  assert(*area1.draw_param_ == 12);
  assert(area1.ctm_.has_value());
  assert(area1.ctm_->to_string() == "1 0 0 1 10 0");
  assert(std::holds_alternative<std::unique_ptr<path_t>>(area1.ops_));
  const auto &path1 = std::get<std::unique_ptr<path_t> >(area1.ops_);
  assert(path1->boundary_.to_string() == "57.5 97.8 5 5");
  assert(path1->stroke_.has_value() && *path1->stroke_ == false);
  assert(path1->fill_.has_value() && *path1->fill_ == true);
  assert(path1->rule_.has_value() && *path1->rule_ == "Even-Odd");
  assert(path1->abbreviated_data_ == "M 10 10 L 80 10 L 80 30 L 10 30 C");
  const clip_t &clip2 = clips.clip_[1];
  const auto &area2 = clip2.area_;
  assert(area2.draw_param_.has_value());
  assert(*area2.draw_param_ == 13);
  assert(!area2.ctm_.has_value());
  assert(std::holds_alternative<std::unique_ptr<text_t>>(area2.ops_));
  const auto &text2 = std::get<std::unique_ptr<text_t> >(area2.ops_);
  assert(text2->boundary_.to_string() == "0 0 50 20");
  assert(text2->font_ == 6);
  assert(text2->size_ == 10.0);
  assert(text2->text_code_.size() == 1);
  const auto &text_code2 = text2->text_code_[0];
  assert(text_code2.x_->to_string() == "0" && text_code2.y_->to_string() == "15");
  assert(text_code2.leaf_value_ == "Clip");
  assert(text_obj.fill_color_ != nullptr);
  const color_t &fill_color = *text_obj.fill_color_;
  assert(fill_color.value_.has_value());
  assert(fill_color.value_->to_string() == "255 0 0");
  assert(fill_color.color_space_.has_value());
  assert(*fill_color.color_space_ == 11);
  assert(fill_color.alpha_.has_value());
  assert(*fill_color.alpha_ == 255);
  assert(text_obj.stroke_color_ != nullptr);
  const color_t &stroke_color = *text_obj.stroke_color_;
  assert(stroke_color.complex_color_ops_.has_value());
  assert(std::holds_alternative<pattern_t>(*stroke_color.complex_color_ops_));
  const pattern_t &pattern = std::get<pattern_t>(*stroke_color.complex_color_ops_);
  assert(pattern.width_ == 10.0);
  assert(pattern.height_ == 10.0);
  assert(pattern.x_step_.has_value() && *pattern.x_step_ == 12.0);
  assert(pattern.y_step_.has_value() && *pattern.y_step_ == 12.0);
  assert(pattern.reflect_method_.has_value() && *pattern.reflect_method_ == "Normal");
  assert(pattern.relative_to_.has_value() && *pattern.relative_to_ == "Object");
  assert(pattern.ctm_.has_value());
  assert(pattern.ctm_->to_string() == "1 0 0 1 5 5");
  const cell_content_t& cell_content = pattern.cell_content_;
  assert(cell_content.page_block_ops_.size() == 1);
  assert(std::holds_alternative<_path_t>(cell_content.page_block_ops_[0]));
  const _path_t& pattern_path = std::get<_path_t>(cell_content.page_block_ops_[0]);
  assert(pattern_path.id_ == 21);
  assert(pattern_path.boundary_.to_string() == "0 0 10 10");
  assert(pattern_path.stroke_.has_value() && *pattern_path.stroke_ == false);
  assert(pattern_path.fill_.has_value() && *pattern_path.fill_ == true);
  assert(pattern_path.abbreviated_data_ == "M 0 0 L 10 10");
  assert(!cell_content.thumbnail_.has_value());

  assert(text_obj.cg_transform_.size() == 2);
  const cg_transform_t &cg1 = text_obj.cg_transform_[0];
  assert(cg1.code_position_ == 0);
  assert(cg1.code_count_ == 2);
  assert(cg1.glyph_count_ == 2);
  assert(cg1.glyphs_.has_value());
  assert(cg1.glyphs_->to_string() == "1001 1002");
  assert(text_obj.text_code_.size() == 2);

  const text_code_t &tc1 = text_obj.text_code_[0];
  assert(tc1.x_.has_value());
  assert(tc1.x_->size() == 1);
  assert((*tc1.x_)[0] == 20.0);

  assert(tc1.y_.has_value());
  assert(tc1.y_->size() == 1);
  assert((*tc1.y_)[0] == 35.0);

  assert(tc1.delta_x_.has_value());
  assert(tc1.delta_x_->size() == 2);
  assert((*tc1.delta_x_)[0] == 10.0);
  assert((*tc1.delta_x_)[1] == 10.0);

  assert(tc1.delta_y_.has_value());
  assert(tc1.delta_y_->size() == 2);
  assert((*tc1.delta_y_)[0] == 0.0);
  assert((*tc1.delta_y_)[1] == 0.0);

  assert(tc1.leaf_value == "文本1");

  // 第二个 TextCode: X="40" Y="35" DeltaX="10 10" DeltaY="0 0">文本2
  const text_code_t &tc2 = text_obj.text_code_[1];
  assert(tc2.x_.has_value());
  assert(tc2.x_->size() == 1);
  assert((*tc2.x_)[0] == 40.0);

  assert(tc2.y_.has_value());
  assert(tc2.y_->size() == 1);
  assert((*tc2.y_)[0] == 35.0);

  assert(tc2.delta_x_.has_value());
  assert(tc2.delta_x_->size() == 2);
  assert((*tc2.delta_x_)[0] == 10.0);
  assert((*tc2.delta_x_)[1] == 10.0);

  assert(tc2.delta_y_.has_value());
  assert(tc2.delta_y_->size() == 2);
  assert((*tc2.delta_y_)[0] == 0.0);
  assert((*tc2.delta_y_)[1] == 0.0);

  assert(tc2.leaf_value == "文本2");

  serialize(page, "page/baseline.xml");
}

void test_annotation() {
  auto annotation = deserialize<page_annot_t>("annotation/baseline.xml");

  serialize(annotation, "annotation/baseline.xml");
}

void test_annotations() {
  auto annotations = deserialize<annotations_t>("annotations/baseline.xml");

  serialize(annotations, "annotations/baseline.xml");
}

void test_attachments() {
  auto attachments = deserialize<attachments_t>("attachments/baseline.xml");

  serialize(attachments, "attachments/baseline.xml");
}

void test_custom_tags() {
  auto custom_tags = deserialize<custom_tags_t>("custom_tags/baseline.xml");

  serialize(custom_tags, "custom_tags/baseline.xml");
}

void test_extensions() {
  auto extensions = deserialize<extensions_t>("extensions/baseline.xml");

  serialize(extensions, "extensions/baseline.xml");
}

void test_res() {
  auto res = deserialize<res_t>("res/baseline.xml");
  serialize(res, "res/baseline.xml");
}

int main() {
  test_ofd();
  test_document();
  test_page();
  test_annotation();
  test_annotations();
  test_attachments();
  test_custom_tags();
  test_extensions();
  test_res();

  return 0;
}
