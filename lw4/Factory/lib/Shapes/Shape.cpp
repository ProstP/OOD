#include "Shape.h"

void Shapes::Shape::SetColor(Color color)
{
	m_color = color;
}

Shapes::Color Shapes::Shape::GetColor() const
{
	return m_color;
}
