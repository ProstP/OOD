#include "TextFigure.h"
#include "../../ConvertDoubleToStringWithoutZero.h"
#include <regex>

TextFigure::TextFigure(const std::string& params)
{
	std::regex pattern("^\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s(.+)$");
	std::smatch match;
	if (!std::regex_match(params, match, pattern))
	{
		throw std::invalid_argument("Invalid paramóters fot text");
	}

	m_text = match[4];
	try
	{
		m_left = std::stod(match[1]);
		m_top = std::stod(match[2]);
		m_fontSize = std::stoi(match[3]);
	}
	catch (...)
	{
		throw std::invalid_argument("Text parametrs expect text must be digits");
	}
}

void TextFigure::Draw(ICanvas& canvas)
{
	canvas.DrawText(m_left, m_top, m_fontSize, m_text);
}

void TextFigure::MoveTo(double dx, double dy)
{
	m_left += dx;
	m_top += dy;
}

std::string TextFigure::GetType() const
{
	return "text";
}

std::string TextFigure::GetParams() const
{
	return ConvertDoubleToString(m_left) + " " + ConvertDoubleToString(m_top) + " " + ConvertDoubleToString(m_fontSize) + " " + m_text;
}
