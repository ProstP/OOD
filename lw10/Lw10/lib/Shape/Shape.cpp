#include "Shape.h"

void Shapes::Shape::SetRect(Types::Rect rect)
{
	m_rect = rect;
}

Types::Rect Shapes::Shape::GetRect() const
{
	return m_rect;
}

void Shapes::Shape::Move(int dx, int dy)
{
	m_rect.left += dx;
	m_rect.top += dy;
}

void Shapes::Shape::Resize(int width, int height)
{
	m_rect.width = width;
	m_rect.height = height;
}

void Shapes::Shape::Draw(Canvas::ICanvas& canvas) const
{
	DrawImp(canvas);
}
