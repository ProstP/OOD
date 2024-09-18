#pragma once
#include "../Gfx/ICanvas.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../WindowCanvas/WindowCanvas.h"

class Canvas : public ICanvas
{
public:
	Canvas(WindowCanvas* window);

	void MoveTo(double x, double y) override;
	void SetColor(const Color& color) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void DrawText(double left, double top, int fontSize, const std::string& text) override;

	~Canvas();

private:
	//std::shared_ptr<sf::RenderTarget> m_window;
	sf::Font m_font;
	WindowCanvas* m_window;
	double m_x;
	double m_y;
	sf::Color m_color;
	std::vector<std::shared_ptr<sf::Drawable>> m_shapes;
	//sf::Thread m_thread;
};
