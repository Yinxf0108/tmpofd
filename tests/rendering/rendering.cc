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

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkRect.h"
#include "include/core/SkStream.h"
#include "include/core/SkFont.h"
#include "include/core/SkData.h"
#include "include/svg/SkSVGCanvas.h"

#include <iostream>
#include <fstream>
#include <memory>

int main() {
  std::cout << "Creating an SVG file with Skia..." << std::endl;

  try {
    // 1. 定义SVG的尺寸
    SkRect bounds = SkRect::MakeIWH(300, 200);

    // 2. 创建一个内存流，用于接收SVG数据
    SkDynamicMemoryWStream stream;

    // 3. 创建一个SkSVGCanvas，它会将所有绘图操作写入流中
    std::unique_ptr<SkCanvas> canvas = SkSVGCanvas::Make(bounds, &stream);

    // 4. 像在普通画布上一样绘图
    SkPaint paint;
    paint.setAntiAlias(true);

    // 绘制一个蓝色的背景矩形
    paint.setColor(SK_ColorBLUE);
    canvas->drawRect(SkRect::MakeIWH(300, 200), paint);

    // 绘制一个黄色的圆
    paint.setColor(SK_ColorYELLOW);
    canvas->drawCircle(150, 100, 80, paint);

    // 绘制文本
    SkFont font;
    font.setSize(24);
    paint.setColor(SK_ColorBLACK);
    canvas->drawString("Hello, SVG!", 85, 105, font, paint);

    // 5. 当canvas对象被销毁时，它会自动完成所有SVG的写入操作
    //    我们手动重置它来确保写入完成
    canvas.reset();

    // 6. 从流中获取数据并写入文件
    sk_sp<SkData> svgData = stream.detachAsData();

    std::ofstream file("created_by_skia.svg");
    if (file.is_open()) {
      file.write(static_cast<const char *>(svgData->data()), svgData->size());
      file.close();
      std::cout << "✓ Successfully created 'created_by_skia.svg'" << std::endl;
    } else {
      std::cerr << "✗ Failed to open file for writing." << std::endl;
      return 1;
    }

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }
}
