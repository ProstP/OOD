#pragma once
#include "../Shapes/lib/Gfx/ICanvas.h"

class Canvas : public ICanvas
{
public:
	Canvas();

	void MoveTo(double x, double y) override;
	void SetColor(const Color& color) override;
	void LineTo(double x, double y) override;
	void DrawEpplise(double cx, double cy, double rx, double ry) override;
	void DrawText(double left, double top, int fontSize, const std::string& text) override;

	~Canvas() = default;
};
