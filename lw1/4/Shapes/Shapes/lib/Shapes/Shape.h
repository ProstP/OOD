#pragma once
#include "../DrawingStrategy/IDrawingStrategy.h"
#include "../Gfx/Color.h"
#include "../Gfx/ICanvas.h"

class Shape
{
public:
	Shape(const std::string& id, const Color& color, const IDrawingStrategy drawingStrategy)
		: m_id{ id }
		, m_color{ color }
		, m_drawingStrategy{ drawingStrategy } {};
	std::string GetId();
	void SetDrawingStrategy(const IDrawingStrategy& drawingStrategy);
	void SetColor(const Color& color);
	Color GetColor() const;
	void MoveShape(double dx, double dy);
	void Draw(ICanvas& canvas);

	std::string ToString() const;

private:
	std::string m_id;
	Color m_color;
	IDrawingStrategy m_drawingStrategy;
};
