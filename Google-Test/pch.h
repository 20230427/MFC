// pch.h
#pragma once

// Google Test
#include "gtest/gtest.h"

// 标准库
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

// Windows API (如果需要)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

// 颜色定义
enum class Color : DWORD {
    BLACK = RGB(0, 0, 0),
    WHITE = RGB(255, 255, 255),
    RED = RGB(255, 0, 0),
    GREEN = RGB(0, 255, 0),
    BLUE = RGB(0, 0, 255),
    YELLOW = RGB(255, 255, 0),
    CYAN = RGB(0, 255, 255),
    MAGENTA = RGB(255, 0, 255),
    GRAY = RGB(128, 128, 128),
    DARK_GRAY = RGB(64, 64, 64),
    LIGHT_GRAY = RGB(192, 192, 192)
};

// 画笔样式
enum class PenStyle : int {
    SOLID = PS_SOLID,
    DASH = PS_DASH,
    DOT = PS_DOT,
    DASHDOT = PS_DASHDOT,
    DASHDOTDOT = PS_DASHDOTDOT
};

// 画笔信息结构
struct PenInfo {
    int width;
    Color color;
    PenStyle style;

    PenInfo(int w = 1, Color c = Color::BLACK, PenStyle s = PenStyle::SOLID)
        : width(w), color(c), style(s) {
    }

    bool operator==(const PenInfo& other) const {
        return width == other.width && color == other.color && style == other.style;
    }

    bool operator!=(const PenInfo& other) const {
        return !(*this == other);
    }
};

// 画刷信息结构
struct BrushInfo {
    Color color;

    BrushInfo(Color c = Color::WHITE) : color(c) {}

    bool operator==(const BrushInfo& other) const {
        return color == other.color;
    }

    bool operator!=(const BrushInfo& other) const {
        return !(*this == other);
    }
};

// Mock CDC 类（扩展版本用于测试）
class MockCDC {
public:
    struct Point {
        int x, y;
        Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct Line {
        Point start, end;
        PenInfo pen;

        Line(Point s, Point e, PenInfo p = PenInfo())
            : start(s), end(e), pen(p) {
        }

        bool operator==(const Line& other) const {
            return start == other.start && end == other.end && pen == other.pen;
        }
    };

    struct Rect {
        int left, top, right, bottom;
        PenInfo pen;
        BrushInfo brush;

        Rect(int l = 0, int t = 0, int r = 0, int b = 0,
            PenInfo p = PenInfo(), BrushInfo br = BrushInfo())
            : left(l), top(t), right(r), bottom(b), pen(p), brush(br) {
        }

        bool operator==(const Rect& other) const {
            return left == other.left && top == other.top &&
                right == other.right && bottom == other.bottom &&
                pen == other.pen && brush == other.brush;
        }
    };

    struct Circle {
        int left, top, right, bottom;
        PenInfo pen;
        BrushInfo brush;

        Circle(int l = 0, int t = 0, int r = 0, int b = 0,
            PenInfo p = PenInfo(), BrushInfo br = BrushInfo())
            : left(l), top(t), right(r), bottom(b), pen(p), brush(br) {
        }

        bool operator==(const Circle& other) const {
            return left == other.left && top == other.top &&
                right == other.right && bottom == other.bottom &&
                pen == other.pen && brush == other.brush;
        }
    };

private:
    Point currentPos;
    PenInfo currentPen;
    BrushInfo currentBrush;

public:
    std::vector<Line> lines;
    std::vector<Rect> rectangles;
    std::vector<Circle> ellipses;

    MockCDC() : currentPos(0, 0), currentPen(), currentBrush() {}

    // 基本绘图操作
    void MoveTo(int x, int y) {
        currentPos = Point(x, y);
    }

    void LineTo(int x, int y) {
        lines.push_back(Line(currentPos, Point(x, y), currentPen));
        currentPos = Point(x, y);
    }

    void Rectangle(int x1, int y1, int x2, int y2) {
        rectangles.push_back(Rect(x1, y1, x2, y2, currentPen, currentBrush));
    }

    void Ellipse(int x1, int y1, int x2, int y2) {
        ellipses.push_back(Circle(x1, y1, x2, y2, currentPen, currentBrush));
    }

    // 画笔设置
    void SetPen(const PenInfo& pen) {
        currentPen = pen;
    }

    void SetPenColor(Color color) {
        currentPen.color = color;
    }

    void SetPenWidth(int width) {
        currentPen.width = width;
    }

    void SetPenStyle(PenStyle style) {
        currentPen.style = style;
    }

    // 画刷设置
    void SetBrush(const BrushInfo& brush) {
        currentBrush = brush;
    }

    void SetBrushColor(Color color) {
        currentBrush.color = color;
    }

    // 获取当前设置
    const PenInfo& GetCurrentPen() const { return currentPen; }
    const BrushInfo& GetCurrentBrush() const { return currentBrush; }
    const Point& GetCurrentPosition() const { return currentPos; }

    // 清除所有内容
    void Clear() {
        lines.clear();
        rectangles.clear();
        ellipses.clear();
        currentPos = Point(0, 0);
        currentPen = PenInfo();
        currentBrush = BrushInfo();
    }

    // 统计方法
    size_t GetLineCount() const { return lines.size(); }
    size_t GetRectangleCount() const { return rectangles.size(); }
    size_t GetEllipseCount() const { return ellipses.size(); }

    // 获取最后绘制的图形
    const Line* GetLastLine() const {
        return lines.empty() ? nullptr : &lines.back();
    }

    const Rect* GetLastRectangle() const {
        return rectangles.empty() ? nullptr : &rectangles.back();
    }

    const Circle* GetLastEllipse() const {
        return ellipses.empty() ? nullptr : &ellipses.back();
    }
};
