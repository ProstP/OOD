#include "Shape.h"
#include <iostream>

void Shapes::Shape::SetColor(const std::string& color)
{
	if (color == "red")
	{
		m_color = Color::Red;
	}
	else if (color == "green")
	{
		m_color = Color::Green;
	}
	else if (color == "blue")
	{
		m_color = Color::Blue;
	}
	else if (color == "pink")
	{
		m_color = Color::Pink;
	}
	else if (color == "yellow")
	{
		m_color = Color::Yellow;
	}
	else if (color == "black")
	{
		m_color = Color::Black;
	}
	else
	{
		throw std::invalid_argument("Unknown color");
	}
}

Shapes::Color Shapes::Shape::GetColor() const
{
	return m_color;
}
