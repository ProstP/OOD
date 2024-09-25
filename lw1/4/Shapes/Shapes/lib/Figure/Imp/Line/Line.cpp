#include "Line.h"
#include "../../ConvertDoubleToStringWithoutZero.h"
#include <regex>

Line::Line(const std::string params)
{
	std::regex pattern("^\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid parameters for line");
	}

	try
	{
		m_x1 = std::stod(match[1]);
		m_y1 = std::stod(match[2]);
		m_x2 = std::stod(match[3]);
		m_y2 = std::stod(match[4]);
	}
	catch (...)
	{
		throw std::invalid_argument("Line parametrs must be digits");
	}
}

void Line::Draw(ICanvas& canvas)
{
	canvas.MoveTo(m_x1, m_y1);
	canvas.LineTo(m_x2, m_y2);
}

void Line::MoveTo(double dx, double dy)
{
	m_x1 += dx;
	m_x2 += dx;
	m_y1 += dy;
	m_y2 += dy;
}

std::string Line::GetType() const
{
	return "line";
}

std::string Line::GetParams() const
{
	return ConvertDoubleToString(m_x1) + " " + ConvertDoubleToString(m_y1) + " " + ConvertDoubleToString(m_x2) + " " + ConvertDoubleToString(m_y2);
}