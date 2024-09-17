#include "Shape.h"

std::string Shape::GetId()
{
	return std::string();
}

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

void Shape::MoveShape(double dx, double dy)
{
	m_drawingStrategy.MoveTo(dx, dy);
}

void Shape::Draw(ICanvas& canvas)
{
	m_drawingStrategy.Draw(canvas);
}

std::string Shape::ToString() const
{
	return std::string();
}
