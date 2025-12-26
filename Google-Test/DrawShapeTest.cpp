// DrawShapeTest.cpp
#include "pch.h"

class DrawShapeTest : public ::testing::Test {
protected:
    void SetUp() override {
        cdc.Clear();
    }

    MockCDC cdc;
};

// 测试直线绘制
TEST_F(DrawShapeTest, DrawLine) {
    cdc.MoveTo(0, 0);
    cdc.LineTo(10, 10);

    ASSERT_EQ(cdc.GetLineCount(), 1u);
    EXPECT_EQ(cdc.lines[0].start.x, 0);
    EXPECT_EQ(cdc.lines[0].start.y, 0);
    EXPECT_EQ(cdc.lines[0].end.x, 10);
    EXPECT_EQ(cdc.lines[0].end.y, 10);
}

// 测试矩形绘制
TEST_F(DrawShapeTest, DrawRectangle) {
    cdc.Rectangle(5, 5, 15, 15);

    ASSERT_EQ(cdc.GetRectangleCount(), 1u);
    EXPECT_EQ(cdc.rectangles[0].left, 5);
    EXPECT_EQ(cdc.rectangles[0].top, 5);
    EXPECT_EQ(cdc.rectangles[0].right, 15);
    EXPECT_EQ(cdc.rectangles[0].bottom, 15);
}

// 测试圆形绘制
TEST_F(DrawShapeTest, DrawEllipse) {
    cdc.Ellipse(0, 0, 20, 20);

    ASSERT_EQ(cdc.GetEllipseCount(), 1u);
    EXPECT_EQ(cdc.ellipses[0].left, 0);
    EXPECT_EQ(cdc.ellipses[0].top, 0);
    EXPECT_EQ(cdc.ellipses[0].right, 20);
    EXPECT_EQ(cdc.ellipses[0].bottom, 20);
}

// 测试MoveTo操作
TEST_F(DrawShapeTest, MoveTo) {
    cdc.MoveTo(10, 20);

    const MockCDC::Point& pos = cdc.GetCurrentPosition();
    EXPECT_EQ(pos.x, 10);
    EXPECT_EQ(pos.y, 20);
}

// 测试带颜色和线宽的形状绘制
TEST_F(DrawShapeTest, DrawShapeWithProperties) {
    // 设置画笔属性
    cdc.SetPenColor(Color::RED);
    cdc.SetPenWidth(3);
    cdc.SetBrushColor(Color::BLUE);

    // 绘制矩形
    cdc.Rectangle(0, 0, 50, 30);

    ASSERT_EQ(cdc.GetRectangleCount(), 1u);
    const MockCDC::Rect& rect = cdc.rectangles[0];

    EXPECT_EQ(rect.pen.color, Color::RED);
    EXPECT_EQ(rect.pen.width, 3);
    EXPECT_EQ(rect.brush.color, Color::BLUE);
    EXPECT_EQ(rect.left, 0);
    EXPECT_EQ(rect.top, 0);
    EXPECT_EQ(rect.right, 50);
    EXPECT_EQ(rect.bottom, 30);
}

// 测试连续绘制多个形状
TEST_F(DrawShapeTest, MultipleShapes) {
    cdc.Rectangle(0, 0, 10, 10);
    cdc.Ellipse(20, 20, 30, 30);
    cdc.MoveTo(5, 5);
    cdc.LineTo(25, 25);

    EXPECT_EQ(cdc.GetRectangleCount(), 1u);
    EXPECT_EQ(cdc.GetEllipseCount(), 1u);
    EXPECT_EQ(cdc.GetLineCount(), 1u);
}

// 测试连续直线绘制
TEST_F(DrawShapeTest, MultipleLines) {
    cdc.MoveTo(0, 0);
    cdc.LineTo(10, 0);
    cdc.LineTo(10, 10);
    cdc.LineTo(0, 10);
    cdc.LineTo(0, 0);

    ASSERT_EQ(cdc.GetLineCount(), 4u);

    // 验证第一条线
    EXPECT_EQ(cdc.lines[0].start.x, 0);
    EXPECT_EQ(cdc.lines[0].start.y, 0);
    EXPECT_EQ(cdc.lines[0].end.x, 10);
    EXPECT_EQ(cdc.lines[0].end.y, 0);

    // 验证第二条线
    EXPECT_EQ(cdc.lines[1].start.x, 10);
    EXPECT_EQ(cdc.lines[1].start.y, 0);
    EXPECT_EQ(cdc.lines[1].end.x, 10);
    EXPECT_EQ(cdc.lines[1].end.y, 10);

    // 验证最后一条线
    EXPECT_EQ(cdc.lines[3].start.x, 0);
    EXPECT_EQ(cdc.lines[3].start.y, 10);
    EXPECT_EQ(cdc.lines[3].end.x, 0);
    EXPECT_EQ(cdc.lines[3].end.y, 0);
}

// 测试不同大小的矩形
TEST_F(DrawShapeTest, DifferentSizedRectangles) {
    cdc.Rectangle(0, 0, 10, 10);
    cdc.Rectangle(20, 20, 40, 50);
    cdc.Rectangle(-5, -5, 5, 5);

    ASSERT_EQ(cdc.GetRectangleCount(), 3u);

    // 验证第一个矩形
    EXPECT_EQ(cdc.rectangles[0].left, 0);
    EXPECT_EQ(cdc.rectangles[0].top, 0);
    EXPECT_EQ(cdc.rectangles[0].right, 10);
    EXPECT_EQ(cdc.rectangles[0].bottom, 10);

    // 验证第二个矩形
    EXPECT_EQ(cdc.rectangles[1].left, 20);
    EXPECT_EQ(cdc.rectangles[1].top, 20);
    EXPECT_EQ(cdc.rectangles[1].right, 40);
    EXPECT_EQ(cdc.rectangles[1].bottom, 50);

    // 验证第三个矩形（负坐标）
    EXPECT_EQ(cdc.rectangles[2].left, -5);
    EXPECT_EQ(cdc.rectangles[2].top, -5);
    EXPECT_EQ(cdc.rectangles[2].right, 5);
    EXPECT_EQ(cdc.rectangles[2].bottom, 5);
}

// 测试不同大小的椭圆
TEST_F(DrawShapeTest, DifferentSizedEllipses) {
    cdc.Ellipse(0, 0, 20, 20);    // 正圆
    cdc.Ellipse(30, 10, 60, 30);  // 椭圆

    ASSERT_EQ(cdc.GetEllipseCount(), 2u);

    // 验证第一个椭圆（正圆）
    EXPECT_EQ(cdc.ellipses[0].left, 0);
    EXPECT_EQ(cdc.ellipses[0].top, 0);
    EXPECT_EQ(cdc.ellipses[0].right, 20);
    EXPECT_EQ(cdc.ellipses[0].bottom, 20);

    // 验证第二个椭圆
    EXPECT_EQ(cdc.ellipses[1].left, 30);
    EXPECT_EQ(cdc.ellipses[1].top, 10);
    EXPECT_EQ(cdc.ellipses[1].right, 60);
    EXPECT_EQ(cdc.ellipses[1].bottom, 30);
}

// 测试清空操作
TEST_F(DrawShapeTest, ClearOperation) {
    // 绘制一些图形
    cdc.Rectangle(0, 0, 10, 10);
    cdc.Ellipse(20, 20, 30, 30);
    cdc.MoveTo(5, 5);
    cdc.LineTo(25, 25);

    // 验证图形已绘制
    EXPECT_EQ(cdc.GetRectangleCount(), 1u);
    EXPECT_EQ(cdc.GetEllipseCount(), 1u);
    EXPECT_EQ(cdc.GetLineCount(), 1u);

    // 清空
    cdc.Clear();

    // 验证已清空
    EXPECT_EQ(cdc.GetRectangleCount(), 0u);
    EXPECT_EQ(cdc.GetEllipseCount(), 0u);
    EXPECT_EQ(cdc.GetLineCount(), 0u);

    // 验证当前位置重置
    const MockCDC::Point& pos = cdc.GetCurrentPosition();
    EXPECT_EQ(pos.x, 0);
    EXPECT_EQ(pos.y, 0);
}

// 测试边界情况
TEST_F(DrawShapeTest, BoundaryValues) {
    // 测试零大小矩形
    cdc.Rectangle(10, 10, 10, 10);

    // 测试负坐标
    cdc.MoveTo(-10, -20);
    cdc.LineTo(-5, -15);

    // 测试大坐标值
    cdc.Ellipse(1000, 1000, 2000, 2000);

    EXPECT_EQ(cdc.GetRectangleCount(), 1u);
    EXPECT_EQ(cdc.GetLineCount(), 1u);
    EXPECT_EQ(cdc.GetEllipseCount(), 1u);

    // 验证负坐标线条
    EXPECT_EQ(cdc.lines[0].start.x, -10);
    EXPECT_EQ(cdc.lines[0].start.y, -20);
    EXPECT_EQ(cdc.lines[0].end.x, -5);
    EXPECT_EQ(cdc.lines[0].end.y, -15);
}

// 测试画笔属性在形状间的传递
TEST_F(DrawShapeTest, PenPropertyPersistence) {
    // 设置画笔属性
    cdc.SetPenColor(Color::RED);
    cdc.SetPenWidth(5);

    // 绘制多个形状
    cdc.Rectangle(0, 0, 10, 10);
    cdc.Ellipse(20, 20, 30, 30);
    cdc.MoveTo(40, 40);
    cdc.LineTo(50, 50);

    ASSERT_EQ(cdc.GetRectangleCount(), 1u);
    ASSERT_EQ(cdc.GetEllipseCount(), 1u);
    ASSERT_EQ(cdc.GetLineCount(), 1u);

    // 验证所有形状都使用相同的画笔属性
    EXPECT_EQ(cdc.rectangles[0].pen.color, Color::RED);
    EXPECT_EQ(cdc.rectangles[0].pen.width, 5);

    EXPECT_EQ(cdc.ellipses[0].pen.color, Color::RED);
    EXPECT_EQ(cdc.ellipses[0].pen.width, 5);

    EXPECT_EQ(cdc.lines[0].pen.color, Color::RED);
    EXPECT_EQ(cdc.lines[0].pen.width, 5);
}

// 测试获取最后绘制的形状
TEST_F(DrawShapeTest, GetLastShape) {
    // 初始状态应该没有形状
    EXPECT_EQ(cdc.GetLastLine(), nullptr);
    EXPECT_EQ(cdc.GetLastRectangle(), nullptr);
    EXPECT_EQ(cdc.GetLastEllipse(), nullptr);

    // 绘制一条线
    cdc.MoveTo(0, 0);
    cdc.LineTo(10, 10);

    const MockCDC::Line* lastLine = cdc.GetLastLine();
    ASSERT_NE(lastLine, nullptr);
    EXPECT_EQ(lastLine->start.x, 0);
    EXPECT_EQ(lastLine->end.x, 10);

    // 绘制一个矩形
    cdc.Rectangle(5, 5, 15, 15);

    const MockCDC::Rect* lastRect = cdc.GetLastRectangle();
    ASSERT_NE(lastRect, nullptr);
    EXPECT_EQ(lastRect->left, 5);
    EXPECT_EQ(lastRect->right, 15);

    // 绘制一个椭圆
    cdc.Ellipse(20, 20, 30, 30);

    const MockCDC::Circle* lastEllipse = cdc.GetLastEllipse();
    ASSERT_NE(lastEllipse, nullptr);
    EXPECT_EQ(lastEllipse->left, 20);
    EXPECT_EQ(lastEllipse->right, 30);
}
