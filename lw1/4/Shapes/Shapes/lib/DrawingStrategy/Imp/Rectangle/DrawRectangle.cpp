#include "DrawRectangle.h"
#include <regex>
#include "../../ConvertDoubleToStringWithoutZero.h"

DrawRectangle::DrawRectangle(const std::string& params)
{
	std::regex pattern("^\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid parameters for rectangle");
	}

	try
	{
		m_left = std::stod(match[1]);
		m_top = std::stod(match[2]);
		m_width = std::stod(match[3]);
		m_height = std::stod(match[4]);
	}
	catch (...)
	{
		throw std::invalid_argument("Rectangle parametrs must be digits");
	}
}

void DrawRectangle::Draw(ICanvas& canvas)
{
	std::cout << "Draw rectangle" << std::endl;
}

void DrawRectangle::MoveTo(double dx, double dy)
{
	m_top += dy;
	m_left += dx;
}

std::string DrawRectangle::GetType() const
{
	return "rectangle";
}

std::string DrawRectangle::GetParams() const
{
	return ConvertDoubleToString(m_left) + " " + ConvertDoubleToString(m_top) + " " + ConvertDoubleToString(m_width) + " " + ConvertDoubleToString(m_height);
}
