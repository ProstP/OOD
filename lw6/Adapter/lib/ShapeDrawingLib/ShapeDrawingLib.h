#pragma once
#include "../GraphicsLib/GraphicsLib.h"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{

struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics\_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color = 0x000000)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
		, m_color(color)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
		canvas.LineTo(m_p3.x, m_p3.y);
		canvas.LineTo(m_p1.x, m_p1.y);
	}

private:
	uint32_t m_color;
	Point m_p1;
	Point m_p2;
	Point m_p3;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point& leftTop, int width, int height, uint32_t color = 0x000000)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
		, m_color(color)
	{
	}
	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

private:
	uint32_t m_color;
	Point m_leftTop;
	int m_width;
	int m_height;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas& canvas)
		: m_canvasPtr(&canvas)
	{
	}
	void Draw(const ICanvasDrawable& drawable)
	{
		drawable.Draw(*m_canvasPtr);
	}

private:
	graphics_lib::ICanvas* m_canvasPtr;
};

} // namespace shape_drawing_lib
