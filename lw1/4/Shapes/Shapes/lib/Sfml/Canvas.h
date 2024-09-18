#pragma once
#include "../Gfx/ICanvas.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Canvas : public ICanvas
{
public:
	Canvas(std::shared_ptr<sf::RenderTarget> window);

	void MoveTo(double x, double y) override;
	void SetColor(const Color& color) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void DrawText(double left, double top, int fontSize, const std::string& text) override;

	~Canvas() = default;

private:
	std::shared_ptr<sf::RenderTarget> m_window;
	double m_x = 0;
	double m_y = 0;
	sf::Color m_color;
	sf::Font m_font;
	//std::vector<std::shared_ptr<sf::Drawable>> m_shapes;
	//sf::Thread m_thread;
};
