#pragma once
#include "../Shapes/lib/Gfx/ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas
{
public:
	Canvas();

	void MoveTo(double x, double y) override;
	void SetColor(const Color& color) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void DrawText(double left, double top, int fontSize, const std::string& text) override;
	void Close() override;

	~Canvas() = default;

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	double m_x;
	double m_y;
	sf::Color m_color;
};
