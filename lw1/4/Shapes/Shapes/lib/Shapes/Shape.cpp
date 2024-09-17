#include "Shape.h"

Shape::Shape(const std::string& id, const Color& color, std::unique_ptr<IDrawingStrategy>&& drawingStrategy)
	: m_id{ id }
	, m_color{ color }
{
	SetDrawingStrategy(std::move(drawingStrategy));
}

std::string Shape::GetId() const
{
	return m_id;
}

void Shape::SetDrawingStrategy(std::unique_ptr<IDrawingStrategy>&& drawingStrategy)
{
	m_drawingStrategy = std::move(drawingStrategy);
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
	m_drawingStrategy->MoveTo(dx, dy);
}

void Shape::Draw(ICanvas& canvas)
{
	m_drawingStrategy->Draw(canvas);
}

std::string Shape::ToString() const
{
	return m_drawingStrategy->GetType() + " " + GetId() + " #" + m_color.GetInHex() + " " + m_drawingStrategy->GetParams();
}
