#include "Shape.h"

Shape::Shape(const std::string& id, const Color& color, std::unique_ptr<IFigure>&& figure)
	: m_id{ id }
	, m_color{ color }
{
	SetFigure(std::move(figure));
}

std::string Shape::GetId() const
{
	return m_id;
}

void Shape::SetFigure(std::unique_ptr<IFigure>&& figure)
{
	m_figure = std::move(figure);
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
	m_figure->MoveTo(dx, dy);
}

void Shape::Draw(ICanvas& canvas)
{
	canvas.SetColor(m_color);
	m_figure->Draw(canvas);
}

std::string Shape::ToString() const
{
	return m_figure->GetType() + " " + GetId() + " #" + m_color.GetInHex() + " " + m_figure->GetParams();
}
