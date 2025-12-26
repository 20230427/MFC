#include "pch.h"
#include "DrawShape.h"

CDrawShape::CDrawShape()
{
    m_type = SHAPE_LINE;
    m_color = Color::Black;
    m_lineWidth = 2.0f;
    m_startPoint = PointF(0, 0);
    m_endPoint = PointF(0, 0);
}

CDrawShape::~CDrawShape()
{
}

void CDrawShape::Draw(Graphics* pGraphics)
{
    // 基类不实现具体绘制
}

std::shared_ptr<CDrawShape> CDrawShape::Clone()
{
    return nullptr;
}

// CLineShape 实现
CLineShape::CLineShape()
{
    m_type = SHAPE_LINE;
}

void CLineShape::Draw(Graphics* pGraphics)
{
    Pen pen(m_color, m_lineWidth);
    pen.SetLineCap(LineCapRound, LineCapRound, DashCapRound);
    pGraphics->DrawLine(&pen, m_startPoint, m_endPoint);
}

std::shared_ptr<CDrawShape> CLineShape::Clone()
{
    auto pShape = std::make_shared<CLineShape>();
    pShape->m_color = m_color;
    pShape->m_lineWidth = m_lineWidth;
    pShape->m_startPoint = m_startPoint;
    pShape->m_endPoint = m_endPoint;
    return pShape;
}

// CRectangleShape 实现
CRectangleShape::CRectangleShape()
{
    m_type = SHAPE_RECTANGLE;
}

void CRectangleShape::Draw(Graphics* pGraphics)
{
    Pen pen(m_color, m_lineWidth);
    RectF rect(min(m_startPoint.X, m_endPoint.X),
        min(m_startPoint.Y, m_endPoint.Y),
        abs(m_endPoint.X - m_startPoint.X),
        abs(m_endPoint.Y - m_startPoint.Y));
    pGraphics->DrawRectangle(&pen, rect);
}

std::shared_ptr<CDrawShape> CRectangleShape::Clone()
{
    auto pShape = std::make_shared<CRectangleShape>();
    pShape->m_color = m_color;
    pShape->m_lineWidth = m_lineWidth;
    pShape->m_startPoint = m_startPoint;
    pShape->m_endPoint = m_endPoint;
    return pShape;
}

// CEllipseShape 实现
CEllipseShape::CEllipseShape()
{
    m_type = SHAPE_ELLIPSE;
}

void CEllipseShape::Draw(Graphics* pGraphics)
{
    Pen pen(m_color, m_lineWidth);
    RectF rect(min(m_startPoint.X, m_endPoint.X),
        min(m_startPoint.Y, m_endPoint.Y),
        abs(m_endPoint.X - m_startPoint.X),
        abs(m_endPoint.Y - m_startPoint.Y));
    pGraphics->DrawEllipse(&pen, rect);
}

std::shared_ptr<CDrawShape> CEllipseShape::Clone()
{
    auto pShape = std::make_shared<CEllipseShape>();
    pShape->m_color = m_color;
    pShape->m_lineWidth = m_lineWidth;
    pShape->m_startPoint = m_startPoint;
    pShape->m_endPoint = m_endPoint;
    return pShape;
}

// CFreehandShape 实现
CFreehandShape::CFreehandShape()
{
    m_type = SHAPE_FREEHAND;
}

void CFreehandShape::Draw(Graphics* pGraphics)
{
    if (m_points.size() < 2) return;

    Pen pen(m_color, m_lineWidth);
    pen.SetLineCap(LineCapRound, LineCapRound, DashCapRound);
    pen.SetLineJoin(LineJoinRound);

    for (size_t i = 1; i < m_points.size(); i++)
    {
        pGraphics->DrawLine(&pen, m_points[i - 1], m_points[i]);
    }
}

std::shared_ptr<CDrawShape> CFreehandShape::Clone()
{
    auto pShape = std::make_shared<CFreehandShape>();
    pShape->m_color = m_color;
    pShape->m_lineWidth = m_lineWidth;
    pShape->m_points = m_points;
    return pShape;
}
