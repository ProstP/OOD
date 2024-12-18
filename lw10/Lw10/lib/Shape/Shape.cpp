#include "Shape.h"

void Shapes::Shape::SetRect(Types::Rect rect)
{
	if (rect.left < 0)
	{
		int right = rect.left + rect.width;
		rect.left = 0;
		rect.width = right;
	}

	if (rect.top < 0)
	{
		int bottom = rect.top + rect.height;
		rect.top = 0;
		rect.height = bottom;
	}

	if (rect.left + rect.width > Types::CANVAS_WIDTH)
	{
		rect.width = Types::CANVAS_WIDTH - rect.left;
	}

	if (rect.top + rect.height > Types::CANVAS_HEIGHT)
	{
		rect.height = Types::CANVAS_WIDTH - rect.top;
	}

	m_rect = rect;
}

Types::Rect Shapes::Shape::GetRect() const
{
	return m_rect;
}

void Shapes::Shape::Move(int dx, int dy)
{
	if (dx < 0 && abs(dx) > m_rect.left)
	{
		m_rect.left = 0;
	}
	if (dy < 0 && abs(dy) > m_rect.top)
	{
		m_rect.top = 0;
	}

	if (m_rect.left + m_rect.width > Types::CANVAS_WIDTH - dx)
	{
		m_rect.left = Types::CANVAS_WIDTH - m_rect.width;
	}
	else
	{
		m_rect.left += dx;
	}

	if (m_rect.top + m_rect.height > Types::CANVAS_HEIGHT - dy)
	{
		m_rect.top = Types::CANVAS_HEIGHT - m_rect.height;
	}
	else
	{
		m_rect.top += dy;
	}
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
