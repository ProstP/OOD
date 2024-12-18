#pragma once
#include "../Shape/Shape.h"

using namespace Shapes;
using namespace Types;

namespace SimpleShapeFactory
{

class Rectangle : public Shape
{
protected:
	void DrawImp(Canvas::ICanvas& canvas) const override
	{
		Point p1 = { GetRect().left, GetRect().top };
		Point p2 = { GetRect().left, GetRect().top + GetRect().height };
		Point p3 = { GetRect().left + GetRect().width, GetRect().top + GetRect().height };
		Point p4 = { GetRect().left + GetRect().width, GetRect().top };

		canvas.DrawPolygon({ p1, p2, p3, p4 });
	}
};

class Ellipse : public Shape
{
protected:
	void DrawImp(Canvas::ICanvas& canvas) const override
	{
		canvas.DrawEllipse(GetRect());
	}
};

class Triangle : public Shape
{
protected:
	void DrawImp(Canvas::ICanvas& canvas) const override
	{
		Point p1 = { GetRect().left + GetRect().width / 2, GetRect().top };
		Point p2 = { GetRect().left, GetRect().top + GetRect().height };
		Point p3 = { GetRect().left + GetRect().width, GetRect().top + GetRect().height };

		canvas.DrawPolygon({ p1, p2, p3 });
	}
};

} // namespace SimpleShapeFactory
