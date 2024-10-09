#pragma once
#include "../Canvas/ICanvas.h"
#include "../Shapes/Point.h"
#include "../Shapes/Shape.h"
#include <string>

namespace SimpleShapeFactory
{

class Rectangle : public Shapes::Shape
{
public:
	Rectangle(const std::string& params);

	void Draw(Canvas::ICanvas& canvas) override;
	Shapes::Point GetLeftTop() const;
	Shapes::Point GetRightBottom() const;

private:
	Shapes::Point m_lt;
	Shapes::Point m_rb;
};

class Triangle : public Shapes::Shape
{
public:
	Triangle(const std::string& params);

	void Draw(Canvas::ICanvas& canvas) override;
	Shapes::Point GetVertex1() const;
	Shapes::Point GetVertex2() const;
	Shapes::Point GetVertex3() const;

private:
	Shapes::Point m_v1;
	Shapes::Point m_v2;
	Shapes::Point m_v3;
};

class Ellipse : public Shapes::Shape
{
public:
	Ellipse(const std::string& params);

	void Draw(Canvas::ICanvas& canvas) override;
	Shapes::Point GetCenter() const;
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;

private:
	Shapes::Point m_c;
	double m_hr;
	double m_vr;
};

class RegularPolygon : public Shapes::Shape
{
public:
	RegularPolygon(const std::string& params);

	void Draw(Canvas::ICanvas& canvas) override;
	Shapes::Point GetCenter() const;
	double GetRadius() const;
	int GetVertexCount() const;

private:
	Shapes::Point m_center;
	double m_r;
	unsigned int m_count;
};

} // namespace SimpleShapeFactory
