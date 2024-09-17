#pragma once
#include "../DrawingStrategy/IDrawingStrategy.h"
#include "../Gfx/Color.h"
#include "../Gfx/ICanvas.h"

class Shape
{
public:
	Shape(const std::string& id, const Color& color, std::unique_ptr<IDrawingStrategy>&& drawingStrategy);
	std::string GetId() const;
	void SetDrawingStrategy(std::unique_ptr<IDrawingStrategy>&& drawingStrategy);
	void SetColor(const Color& color);
	Color GetColor() const;
	void MoveShape(double dx, double dy);
	void Draw(ICanvas& canvas);

	std::string ToString() const;

private:
	std::string m_id;
	Color m_color;
	std::unique_ptr<IDrawingStrategy> m_drawingStrategy;
};
