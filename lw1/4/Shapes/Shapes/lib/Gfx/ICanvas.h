#pragma once
#include "Color.h"
#include <iostream>

class ICanvas
{
public:
	virtual void MoveTo(double x, double y);
	virtual void SetColor(const Color& color);
	virtual void LineTo(double x, double y);
	virtual void DrawEpplise(double cx, double cy, double rx, double ry);
	virtual void DrawText(double left, double top, int fontSize, const std::string& text);

	virtual ~ICanvas() = default;
};
