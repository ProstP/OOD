#include "Canvas.h"

Canvas::Canvas()
{
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 1000), "Canvas");
	m_x = 0;
	m_y = 0;
	m_color = sf::Color::Black;

	m_window->setVerticalSyncEnabled(true);

	m_window->clear(sf::Color::White);
}

void Canvas::MoveTo(double x, double y)
{
	m_x = x;
	m_y = y;
}

void Canvas::SetColor(const Color& color)
{
	m_color = sf::Color(color.GetR(), color.GetG(), color.GetB(), 255);
}

void Canvas::LineTo(double x, double y)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(static_cast<float>(m_x), static_cast<float>(m_y));
	line[1].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	line[0].color = m_color;
	line[1].color = m_color;

	m_window->draw(line);
	m_window->display();
}

void Canvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	sf::CircleShape circle(static_cast<float>(rx));
	circle.setFillColor(m_color);
	circle.setPosition(static_cast<float>(cx), static_cast<float>(cy));
	double scaleY = ry / rx;
	circle.setScale(1, static_cast<float>(scaleY));

	m_window->draw(circle);
	m_window->display();
}

void Canvas::DrawText(double left, double top, int fontSize, const std::string& text)
{
	sf::Font font;
	if (!font.loadFromFile("SUSE-Medium.ttf"))
	{
		throw std::runtime_error("Filename with font is invalid");
	}

	sf::Text drawText;
	drawText.setPosition(static_cast<float>(left), static_cast<float>(top));
	drawText.setFont(font);
	drawText.setCharacterSize(fontSize);
	drawText.setString(text);

	m_window->draw(drawText);
	m_window->display();
}

void Canvas::Close()
{
	m_window->close();
}
