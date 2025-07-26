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

#include "tmpofd/zip_handler/zip_handler.h"
#include "tmpofd/core/serialization/serialization.h"
#include "tmpofd/core/struct/ofd/ofd.h"
#include "tmpofd/core/struct/document/document.h"
#include "tmpofd/core/struct/page/page.h"

#include <iostream>

using namespace tmpofd;

int main() {
  try {
    ZipHandler::ins().load("测试文件.ofd");

    const auto ofd_content = ZipHandler::ins().get("OFD.xml");
    std::cout << ofd_content << std::endl;

    ofd_t ofd{};
    from_xml(ofd, std::string_view{ofd_content});

    for (const auto &doc_body : ofd.doc_bodies_) {
      const auto document_content = ZipHandler::ins().get(doc_body.doc_root_);
      std::cout << document_content << std::endl;

      document_t document{};
      from_xml(document, std::string_view{document_content});

      for (const auto &[id_, base_loc_] : document.pages_) {
        auto page_content = ZipHandler::ins().get(doc_body.doc_root_.parent_path() / base_loc_);
        std::cout << page_content << std::endl;

        page_t page{};
        from_xml(page, std::string_view{page_content});
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "ZipHandler error : " << e.what() << std::endl;
  }

  return 0;
}
