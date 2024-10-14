#include "SimpleShapes.h"
#include <cmath>
#include <regex>

SimpleShapeFactory::Rectangle::Rectangle(const std::string& color, double ltX, double ltY, double rbX, double rbY)
{
	SetColor(color);

	m_lt = Shapes::Point{ ltX, ltY };
	m_rb = Shapes::Point{ rbX, rbY };
}

void SimpleShapeFactory::Rectangle::Draw(Canvas::ICanvas& canvas)
{
	Shapes::Point rt{ m_rb.x, m_lt.y };
	Shapes::Point lb{ m_lt.x, m_rb.y };

	canvas.SetColor(GetColor());

	canvas.DrawLine(m_lt, rt);
	canvas.DrawLine(rt, m_rb);
	canvas.DrawLine(m_rb, lb);
	canvas.DrawLine(lb, m_lt);
}

Shapes::Point SimpleShapeFactory::Rectangle::GetLeftTop() const
{
	return m_lt;
}

Shapes::Point SimpleShapeFactory::Rectangle::GetRightBottom() const
{
	return m_rb;
}

SimpleShapeFactory::Triangle::Triangle(const std::string& color, double v1x, double v1y, double v2x, double v2y, double v3x, double v3y)
{
	SetColor(color);

	m_v1 = Shapes::Point(v1x, v1y);
	m_v2 = Shapes::Point(v2x, v2y);
	m_v3 = Shapes::Point(v3x, v3y);
}

void SimpleShapeFactory::Triangle::Draw(Canvas::ICanvas& canvas)
{
	canvas.SetColor(GetColor());

	canvas.DrawLine(m_v1, m_v2);
	canvas.DrawLine(m_v2, m_v3);
	canvas.DrawLine(m_v3, m_v1);
}

Shapes::Point SimpleShapeFactory::Triangle::GetVertex1() const
{
	return m_v1;
}

Shapes::Point SimpleShapeFactory::Triangle::GetVertex2() const
{
	return m_v2;
}

Shapes::Point SimpleShapeFactory::Triangle::GetVertex3() const
{
	return m_v3;
}

SimpleShapeFactory::Ellipse::Ellipse(const std::string& color, double cx, double cy, double hr, double vr)
{
	SetColor(color);

	m_c = Shapes::Point{ cx, cy };
	m_hr = hr;
	m_vr = vr;
}

void SimpleShapeFactory::Ellipse::Draw(Canvas::ICanvas& canvas)
{
	canvas.SetColor(GetColor());

	canvas.DrawEllipse(m_c, m_hr, m_vr);
}

Shapes::Point SimpleShapeFactory::Ellipse::GetCenter() const
{
	return m_c;
}

double SimpleShapeFactory::Ellipse::GetHorizontalRadius() const
{
	return m_hr;
}

double SimpleShapeFactory::Ellipse::GetVerticalRadius() const
{
	return m_vr;
}

SimpleShapeFactory::RegularPolygon::RegularPolygon(const std::string& color, double cx, double cy, double r, int count)
{
	SetColor(color);

	m_center = Shapes::Point(cx, cy);
	m_r = r;
	m_count = count;
}

void SimpleShapeFactory::RegularPolygon::Draw(Canvas::ICanvas& canvas)
{
	canvas.SetColor(GetColor());

	const float pi = 2.0f * static_cast<float>(acos(0));
	const float angle = 2.0f * pi / m_count;
	Shapes::Point start{ m_center.x + m_r, m_center.y };

	for (unsigned int i = 1; i <= m_count; i++)
	{
		Shapes::Point end{ m_center.x + m_r * cos(angle * i), m_center.y - m_r * sin(angle * i) };

		canvas.DrawLine(start, end);

		start = end;
	}
}

Shapes::Point SimpleShapeFactory::RegularPolygon::GetCenter() const
{
	return m_center;
}

int SimpleShapeFactory::RegularPolygon::GetVertexCount() const
{
	return m_count;
}

double SimpleShapeFactory::RegularPolygon::GetRadius() const
{
	return m_r;
}
