#pragma once
#include "../Figure/IFigure.h"
#include "../Gfx/Color.h"
#include "../Gfx/ICanvas.h"

class Shape
{
public:
	Shape(const std::string& id, const Color& color, std::unique_ptr<IFigure>&& figure);
	std::string GetId() const;
	void SetFigure(std::unique_ptr<IFigure>&& figure);
	void SetColor(const Color& color);
	Color GetColor() const;
	void MoveShape(double dx, double dy);
	void Draw(ICanvas& canvas);

	std::string ToString() const;

private:
	std::string m_id;
	Color m_color;
	std::unique_ptr<IFigure> m_figure;
};
