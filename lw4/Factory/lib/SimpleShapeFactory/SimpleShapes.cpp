#include "SimpleShapes.h"
#include <cmath>
#include <regex>

SimpleShapeFactory::Rectangle::Rectangle(const std::string& params)
{
	std::regex pattern("^\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid parameters for rectangle");
	}

	try
	{
		m_lt.x = std::stod(match[1]);
		m_lt.y = std::stod(match[2]);
		m_rb.x = std::stod(match[3]);
		m_rb.y = std::stod(match[4]);
	}
	catch (...)
	{
		throw std::invalid_argument("Rectangle parametrs must be digits");
	}
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

SimpleShapeFactory::Triangle::Triangle(const std::string& params)
{
	std::regex pattern("^\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid parameters for triangle");
	}

	try
	{
		m_v1.x = std::stod(match[1]);
		m_v1.y = std::stod(match[2]);
		m_v2.x = std::stod(match[3]);
		m_v2.y = std::stod(match[4]);
		m_v3.x = std::stod(match[5]);
		m_v3.y = std::stod(match[6]);
	}
	catch (...)
	{
		throw std::invalid_argument("Triangle parametrs must be digits");
	}
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

SimpleShapeFactory::Ellipse::Ellipse(const std::string& params)
{
	std::regex pattern("^\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid parameters for circle");
	}

	try
	{
		m_c.x = std::stod(match[1]);
		m_c.y = std::stod(match[2]);
		m_hr = std::stod(match[3]);
		m_vr = std::stod(match[4]);
	}
	catch (...)
	{
		throw std::invalid_argument("Ellipse parametrs must be digits");
	}
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

SimpleShapeFactory::RegularPolygon::RegularPolygon(const std::string& params)
{
	std::regex pattern("^\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\\d+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid parameters for circle");
	}

	try
	{
		m_center.x = std::stod(match[1]);
		m_center.y = std::stod(match[2]);
		m_r = std::stod(match[3]);
		m_count = std::stod(match[4]);
	}
	catch (...)
	{
		throw std::invalid_argument("Invalid parametrs for regular polygon");
	}
}

void SimpleShapeFactory::RegularPolygon::Draw(Canvas::ICanvas& canvas)
{
	canvas.SetColor(GetColor());

	const float pi = 2.0f * acos(0);
	const float angle = 2.0f * pi / m_count;
	Shapes::Point start{ m_center.x + m_r, m_center.y };

	for (int i = 1; i < m_count; i++)
	{
		Shapes::Point end{ m_center.x + m_r * cos(angle), m_center.y - m_r * sin(angle) };

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
