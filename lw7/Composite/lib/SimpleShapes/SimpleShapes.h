#pragma once
#include "../Shape/Shapes.h"

namespace SimpleShapes
{

class Rectangle : public Shapes::Shape
{
public:
	Rectangle(std::shared_ptr<Shapes::IShape> parent)
		: Shape(parent)
	{
	}

protected:
	void DrawImp(Canvas::ICanvas& canvas) const override
	{
		RectD rect = GetFrame();

		canvas.MoveTo(rect.left, rect.top);
		canvas.LineTo(rect.left + rect.width, rect.top);
		canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
		canvas.LineTo(rect.left, rect.top + rect.height);
		canvas.LineTo(rect.left, rect.top);
	}
};

class Triangle : public Shapes::Shape
{
public:
	Triangle(std::shared_ptr<Shapes::IShape> parent)
		: Shape(parent)
	{
	}

protected:
	void DrawImp(Canvas::ICanvas& canvas) const override
	{
		RectD rect = GetFrame();

		canvas.MoveTo(rect.left + rect.width / 2, rect.top);
		canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
		canvas.LineTo(rect.left, rect.top + rect.height);
		canvas.LineTo(rect.left + rect.width / 2, rect.top);
	}
};

class Ellipse : public Shapes::Shape
{
public:
	Ellipse(std::shared_ptr<Shapes::IShape> parent)
		: Shape(parent)
	{
	}

protected:
	void DrawImp(Canvas::ICanvas& canvas) const override
	{
		RectD rect = GetFrame();

		canvas.DrawEllipse(rect.left, rect.top, rect.width, rect.height);
	}
};

} // namespace SimpleShapes
