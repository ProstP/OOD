#include "Shape.h"

void Shape::SetDrawingStrategy(const IDrawingStrategy& drawingStrategy)
{
	m_drawingStrategy = drawingStrategy;
}

void Shape::SetColor(const Color& color)
{
	m_color = color;
}

Color Shape::GetColor() const
{
	return m_color;
}

void Shape::Draw(ICanvas& canvas)
{
	m_drawingStrategy.Draw(canvas);
}

std::string Shape::ToString() const
{
	return std::string();
}
