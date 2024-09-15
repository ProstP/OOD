#pragma once
#include "../DrawingStrategy/IDrawingStrategy.h"
#include "../Gfx/Color.h"
#include "../Gfx/ICanvas.h"

class Shape
{
public:
	void SetDrawingStrategy(const IDrawingStrategy& drawingStrategy);
	void SetColor(const Color& color);
	Color GetColor() const;

	void Draw(ICanvas& canvas);

	std::string ToString() const;

private:
	Color m_color;
	IDrawingStrategy m_drawingStrategy;
};
