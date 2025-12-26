// ColorAndLineWidthTest.cpp
#include "pch.h"

class ColorAndLineWidthTest : public ::testing::Test {
protected:
    void SetUp() override {
        cdc.Clear();
    }

    MockCDC cdc;
};

// ==================== 颜色测试 ====================

// 测试设置画笔颜色
TEST_F(ColorAndLineWidthTest, SetPenColor) {
    cdc.SetPenColor(Color::RED);
    EXPECT_EQ(cdc.GetCurrentPen().color, Color::RED);

    cdc.SetPenColor(Color::BLUE);
    EXPECT_EQ(cdc.GetCurrentPen().color, Color::BLUE);

    cdc.SetPenColor(Color::GREEN);
    EXPECT_EQ(cdc.GetCurrentPen().color, Color::GREEN);
}

// 测试设置画刷颜色
TEST_F(ColorAndLineWidthTest, SetBrushColor) {
    cdc.SetBrushColor(Color::YELLOW);
    EXPECT_EQ(cdc.GetCurrentBrush().color, Color::YELLOW);

    cdc.SetBrushColor(Color::CYAN);
    EXPECT_EQ(cdc.GetCurrentBrush().color, Color::CYAN);

    cdc.SetBrushColor(Color::MAGENTA);
    EXPECT_EQ(cdc.GetCurrentBrush().color, Color::MAGENTA);
}

// 测试带颜色的直线绘制
TEST_F(ColorAndLineWidthTest, DrawLineWithColor) {
    cdc.SetPenColor(Color::RED);
    cdc.MoveTo(0, 0);
    cdc.LineTo(10, 10);

    ASSERT_EQ(cdc.GetLineCount(), 1u);  // 添加u后缀避免类型比较警告
    const MockCDC::Line* line = cdc.GetLastLine();  // 明确指定类型
    ASSERT_NE(line, nullptr);
    EXPECT_EQ(line->pen.color, Color::RED);
    EXPECT_EQ(line->start.x, 0);
    EXPECT_EQ(line->start.y, 0);
    EXPECT_EQ(line->end.x, 10);
    EXPECT_EQ(line->end.y, 10);
}

// 测试带颜色的矩形绘制
TEST_F(ColorAndLineWidthTest, DrawRectangleWithColor) {
    cdc.SetPenColor(Color::BLUE);
    cdc.SetBrushColor(Color::LIGHT_GRAY);
    cdc.Rectangle(5, 5, 15, 15);

    ASSERT_EQ(cdc.GetRectangleCount(), 1u);
    const MockCDC::Rect* rect = cdc.GetLastRectangle();  // 明确指定类型
    ASSERT_NE(rect, nullptr);
    EXPECT_EQ(rect->pen.color, Color::BLUE);
    EXPECT_EQ(rect->brush.color, Color::LIGHT_GRAY);
    EXPECT_EQ(rect->left, 5);
    EXPECT_EQ(rect->top, 5);
    EXPECT_EQ(rect->right, 15);
    EXPECT_EQ(rect->bottom, 15);
}

// 测试带颜色的椭圆绘制
TEST_F(ColorAndLineWidthTest, DrawEllipseWithColor) {
    cdc.SetPenColor(Color::GREEN);
    cdc.SetBrushColor(Color::YELLOW);
    cdc.Ellipse(0, 0, 20, 20);

    ASSERT_EQ(cdc.GetEllipseCount(), 1u);
    const MockCDC::Circle* ellipse = cdc.GetLastEllipse();  // 明确指定类型
    ASSERT_NE(ellipse, nullptr);
    EXPECT_EQ(ellipse->pen.color, Color::GREEN);
    EXPECT_EQ(ellipse->brush.color, Color::YELLOW);
    EXPECT_EQ(ellipse->left, 0);
    EXPECT_EQ(ellipse->top, 0);
    EXPECT_EQ(ellipse->right, 20);
    EXPECT_EQ(ellipse->bottom, 20);
}

// ==================== 线宽测试 ====================

// 测试设置画笔线宽
TEST_F(ColorAndLineWidthTest, SetPenWidth) {
    cdc.SetPenWidth(1);
    EXPECT_EQ(cdc.GetCurrentPen().width, 1);

    cdc.SetPenWidth(3);
    EXPECT_EQ(cdc.GetCurrentPen().width, 3);

    cdc.SetPenWidth(5);
    EXPECT_EQ(cdc.GetCurrentPen().width, 5);

    cdc.SetPenWidth(10);
    EXPECT_EQ(cdc.GetCurrentPen().width, 10);
}

// 测试带线宽的直线绘制
TEST_F(ColorAndLineWidthTest, DrawLineWithWidth) {
    cdc.SetPenWidth(3);
    cdc.MoveTo(0, 0);
    cdc.LineTo(20, 20);

    ASSERT_EQ(cdc.GetLineCount(), 1u);
    const MockCDC::Line* line = cdc.GetLastLine();
    ASSERT_NE(line, nullptr);
    EXPECT_EQ(line->pen.width, 3);
    EXPECT_EQ(line->start.x, 0);
    EXPECT_EQ(line->start.y, 0);
    EXPECT_EQ(line->end.x, 20);
    EXPECT_EQ(line->end.y, 20);
}

// 测试带线宽的矩形绘制
TEST_F(ColorAndLineWidthTest, DrawRectangleWithWidth) {
    cdc.SetPenWidth(5);
    cdc.Rectangle(10, 10, 30, 30);

    ASSERT_EQ(cdc.GetRectangleCount(), 1u);
    const MockCDC::Rect* rect = cdc.GetLastRectangle();
    ASSERT_NE(rect, nullptr);
    EXPECT_EQ(rect->pen.width, 5);
    EXPECT_EQ(rect->left, 10);
    EXPECT_EQ(rect->top, 10);
    EXPECT_EQ(rect->right, 30);
    EXPECT_EQ(rect->bottom, 30);
}

// 测试带线宽的椭圆绘制
TEST_F(ColorAndLineWidthTest, DrawEllipseWithWidth) {
    cdc.SetPenWidth(2);
    cdc.Ellipse(5, 5, 25, 25);

    ASSERT_EQ(cdc.GetEllipseCount(), 1u);
    const MockCDC::Circle* ellipse = cdc.GetLastEllipse();
    ASSERT_NE(ellipse, nullptr);
    EXPECT_EQ(ellipse->pen.width, 2);
    EXPECT_EQ(ellipse->left, 5);
    EXPECT_EQ(ellipse->top, 5);
    EXPECT_EQ(ellipse->right, 25);
    EXPECT_EQ(ellipse->bottom, 25);
}

// ==================== 画笔样式测试 ====================

// 测试设置画笔样式
TEST_F(ColorAndLineWidthTest, SetPenStyle) {
    cdc.SetPenStyle(PenStyle::SOLID);
    EXPECT_EQ(cdc.GetCurrentPen().style, PenStyle::SOLID);

    cdc.SetPenStyle(PenStyle::DASH);
    EXPECT_EQ(cdc.GetCurrentPen().style, PenStyle::DASH);

    cdc.SetPenStyle(PenStyle::DOT);
    EXPECT_EQ(cdc.GetCurrentPen().style, PenStyle::DOT);

    cdc.SetPenStyle(PenStyle::DASHDOT);
    EXPECT_EQ(cdc.GetCurrentPen().style, PenStyle::DASHDOT);
}

// 测试带样式的直线绘制
TEST_F(ColorAndLineWidthTest, DrawLineWithStyle) {
    cdc.SetPenStyle(PenStyle::DASH);
    cdc.SetPenWidth(2);
    cdc.SetPenColor(Color::RED);
    cdc.MoveTo(0, 0);
    cdc.LineTo(50, 0);

    ASSERT_EQ(cdc.GetLineCount(), 1u);
    const MockCDC::Line* line = cdc.GetLastLine();
    ASSERT_NE(line, nullptr);
    EXPECT_EQ(line->pen.style, PenStyle::DASH);
    EXPECT_EQ(line->pen.width, 2);
    EXPECT_EQ(line->pen.color, Color::RED);
}

// ==================== 综合测试 ====================

// 测试同时设置颜色、线宽和样式
TEST_F(ColorAndLineWidthTest, SetPenAllProperties) {
    PenInfo customPen(4, Color::BLUE, PenStyle::DOT);
    cdc.SetPen(customPen);

    const PenInfo& currentPen = cdc.GetCurrentPen();
    EXPECT_EQ(currentPen.width, 4);
    EXPECT_EQ(currentPen.color, Color::BLUE);
    EXPECT_EQ(currentPen.style, PenStyle::DOT);
}

// 测试复杂图形绘制
TEST_F(ColorAndLineWidthTest, DrawComplexShapes) {
    // 绘制红色粗线矩形
    cdc.SetPenColor(Color::RED);
    cdc.SetPenWidth(3);
    cdc.SetBrushColor(Color::LIGHT_GRAY);
    cdc.Rectangle(0, 0, 50, 30);

    // 绘制蓝色细线圆形
    cdc.SetPenColor(Color::BLUE);
    cdc.SetPenWidth(1);
    cdc.SetBrushColor(Color::YELLOW);
    cdc.Ellipse(60, 0, 90, 30);

    // 绘制绿色虚线
    cdc.SetPenColor(Color::GREEN);
    cdc.SetPenWidth(2);
    cdc.SetPenStyle(PenStyle::DASH);
    cdc.MoveTo(0, 40);
    cdc.LineTo(100, 40);

    // 验证绘制结果
    EXPECT_EQ(cdc.GetRectangleCount(), 1u);
    EXPECT_EQ(cdc.GetEllipseCount(), 1u);
    EXPECT_EQ(cdc.GetLineCount(), 1u);

    // 验证矩形 - 需要按照绘制顺序获取
    ASSERT_EQ(cdc.rectangles.size(), 1u);
    const MockCDC::Rect& rectRef = cdc.rectangles[0];  // 使用引用避免指针问题
    EXPECT_EQ(rectRef.pen.color, Color::RED);
    EXPECT_EQ(rectRef.pen.width, 3);
    EXPECT_EQ(rectRef.brush.color, Color::LIGHT_GRAY);

    // 验证椭圆
    ASSERT_EQ(cdc.ellipses.size(), 1u);
    const MockCDC::Circle& ellipseRef = cdc.ellipses[0];  // 使用引用
    EXPECT_EQ(ellipseRef.pen.color, Color::BLUE);
    EXPECT_EQ(ellipseRef.pen.width, 1);
    EXPECT_EQ(ellipseRef.brush.color, Color::YELLOW);

    // 验证直线
    ASSERT_EQ(cdc.lines.size(), 1u);
    const MockCDC::Line& lineRef = cdc.lines[0];  // 使用引用
    EXPECT_EQ(lineRef.pen.color, Color::GREEN);
    EXPECT_EQ(lineRef.pen.width, 2);
    EXPECT_EQ(lineRef.pen.style, PenStyle::DASH);
}

// 测试不同线宽的多条线
TEST_F(ColorAndLineWidthTest, MultipleLinesWithDifferentWidths) {
    const std::vector<int> widths = { 1, 2, 3, 4, 5 };  // 添加const并初始化

    for (size_t i = 0; i < widths.size(); ++i) {
        cdc.SetPenWidth(widths[i]);
        cdc.MoveTo(static_cast<int>(i * 10), 0);
        cdc.LineTo(static_cast<int>(i * 10), 50);
    }

    ASSERT_EQ(cdc.GetLineCount(), widths.size());

    for (size_t i = 0; i < widths.size(); ++i) {
        EXPECT_EQ(cdc.lines[i].pen.width, widths[i]);
    }
}

// 测试不同颜色的多个形状
TEST_F(ColorAndLineWidthTest, MultipleShapesWithDifferentColors) {
    const std::vector<Color> colors = { Color::RED, Color::GREEN, Color::BLUE, Color::YELLOW };  // 添加const并初始化

    for (size_t i = 0; i < colors.size(); ++i) {
        cdc.SetPenColor(colors[i]);
        int pos = static_cast<int>(i * 20);
        cdc.Rectangle(pos, 0, pos + 15, 15);
    }

    ASSERT_EQ(cdc.GetRectangleCount(), colors.size());

    for (size_t i = 0; i < colors.size(); ++i) {
        EXPECT_EQ(cdc.rectangles[i].pen.color, colors[i]);
    }
}

// 测试颜色值的正确性
TEST_F(ColorAndLineWidthTest, ColorValues) {
    EXPECT_EQ(static_cast<DWORD>(Color::BLACK), RGB(0, 0, 0));
    EXPECT_EQ(static_cast<DWORD>(Color::WHITE), RGB(255, 255, 255));
    EXPECT_EQ(static_cast<DWORD>(Color::RED), RGB(255, 0, 0));
    EXPECT_EQ(static_cast<DWORD>(Color::GREEN), RGB(0, 255, 0));
    EXPECT_EQ(static_cast<DWORD>(Color::BLUE), RGB(0, 0, 255));
    EXPECT_EQ(static_cast<DWORD>(Color::YELLOW), RGB(255, 255, 0));
    EXPECT_EQ(static_cast<DWORD>(Color::CYAN), RGB(0, 255, 255));
    EXPECT_EQ(static_cast<DWORD>(Color::MAGENTA), RGB(255, 0, 255));
}

// 测试默认值
TEST_F(ColorAndLineWidthTest, DefaultValues) {
    MockCDC defaultCdc;

    EXPECT_EQ(defaultCdc.GetCurrentPen().width, 1);
    EXPECT_EQ(defaultCdc.GetCurrentPen().color, Color::BLACK);
    EXPECT_EQ(defaultCdc.GetCurrentPen().style, PenStyle::SOLID);
    EXPECT_EQ(defaultCdc.GetCurrentBrush().color, Color::WHITE);
}

// 测试边界值
TEST_F(ColorAndLineWidthTest, BoundaryValues) {
    // 测试极小线宽
    cdc.SetPenWidth(0);
    EXPECT_EQ(cdc.GetCurrentPen().width, 0);

    // 测试极大线宽
    cdc.SetPenWidth(100);
    EXPECT_EQ(cdc.GetCurrentPen().width, 100);

    // 测试绘制
    cdc.MoveTo(0, 0);
    cdc.LineTo(10, 10);

    ASSERT_EQ(cdc.GetLineCount(), 1u);
    const MockCDC::Line* line = cdc.GetLastLine();
    ASSERT_NE(line, nullptr);
    EXPECT_EQ(line->pen.width, 100);
}
