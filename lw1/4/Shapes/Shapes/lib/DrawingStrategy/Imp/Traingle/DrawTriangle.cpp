#include "DrawTriangle.h"
#include "../../ConvertDoubleToStringWithoutZero.h"
#include <regex>

DrawTriangle::DrawTriangle(const std::string& params)
{
	std::regex pattern("^\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid parameters for triangle");
	}

	try
	{
		m_x1 = std::stod(match[1]);
		m_y1 = std::stod(match[2]);
		m_x2 = std::stod(match[3]);
		m_y2 = std::stod(match[4]);
		m_x3 = std::stod(match[5]);
		m_y3 = std::stod(match[6]);
	}
	catch (...)
	{
		throw std::invalid_argument("Triangle parametrs must be digits");
	}
}

void DrawTriangle::Draw(ICanvas& canvas)
{
	std::cout << "Draw triangle" << std::endl;
}

void DrawTriangle::MoveTo(double dx, double dy)
{
	m_x1 += dx;
	m_x2 += dx;
	m_x3 += dx;
	m_y1 += dy;
	m_y2 += dy;
	m_y3 += dy;
}

std::string DrawTriangle::GetType() const
{
	return "triangle";
}

std::string DrawTriangle::GetParams() const
{
	return ConvertDoubleToString(m_x1) + " " + ConvertDoubleToString(m_y1) + " " + ConvertDoubleToString(m_x2) + " " + ConvertDoubleToString(m_y2) + " " + ConvertDoubleToString(m_x3) + " " + ConvertDoubleToString(m_y3);
}