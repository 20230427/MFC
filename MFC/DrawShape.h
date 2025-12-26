#pragma once
#include "pch.h"

enum ShapeType
{
    SHAPE_LINE = 0,
    SHAPE_RECTANGLE,
    SHAPE_ELLIPSE,
    SHAPE_FREEHAND
};

class CDrawShape
{
public:
    CDrawShape();
    virtual ~CDrawShape();

    ShapeType m_type;
    Color m_color;
    REAL m_lineWidth;
    PointF m_startPoint;
    PointF m_endPoint;
    std::vector<PointF> m_points; // 用于自由曲线

    virtual void Draw(Graphics* pGraphics);
    virtual std::shared_ptr<CDrawShape> Clone();
};

class CLineShape : public CDrawShape
{
public:
    CLineShape();
    virtual void Draw(Graphics* pGraphics) override;
    virtual std::shared_ptr<CDrawShape> Clone() override;
};

class CRectangleShape : public CDrawShape
{
public:
    CRectangleShape();
    virtual void Draw(Graphics* pGraphics) override;
    virtual std::shared_ptr<CDrawShape> Clone() override;
};

class CEllipseShape : public CDrawShape
{
public:
    CEllipseShape();
    virtual void Draw(Graphics* pGraphics) override;
    virtual std::shared_ptr<CDrawShape> Clone() override;
};

class CFreehandShape : public CDrawShape
{
public:
    CFreehandShape();
    virtual void Draw(Graphics* pGraphics) override;
    virtual std::shared_ptr<CDrawShape> Clone() override;
};
