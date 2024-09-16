#include "DrawCircle.h"
#include <regex>
#include <string>
#include "../../ConvertDoubleToStringWithoutZero.h"

DrawCircle::DrawCircle(std::string params)
{
	std::regex pattern("^\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid paramters from circle");
	}

	try
	{
		m_x = std::stod(match[1]);
		m_y = std::stod(match[2]);
		m_r = std::stod(match[3]);
	}
	catch (...)
	{
		throw std::invalid_argument("Circle parametrs must be digits");
	}
}

void DrawCircle::Draw(ICanvas& canvas)
{
	std::cout << "Drawing circle" << std::endl;
}

void DrawCircle::MoveTo(double dx, double dy)
{
	m_x += dx;
	m_y += dy;
}

std::string DrawCircle::GetType() const
{
	return "circle";
}

std::string DrawCircle::GetParams() const
{
	return ConvertDoubleToString(m_x) + " " + ConvertDoubleToString(m_y) + " " + ConvertDoubleToString(m_r);
}
