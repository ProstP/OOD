#include "Canvas.h"

Canvas::Canvas()
	: m_thread(&Canvas::CanvasThread, this)
{
	m_x = 0;
	m_y = 0;
	m_color = sf::Color::Black;
	if (!m_font.loadFromFile("SUSE-Medium.ttf"))
	{
		throw std::runtime_error("Filename with font is invalid");
	}


	m_thread.launch();
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

	m_shapes.push_back(std::make_shared<sf::VertexArray>(line));
}

void Canvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	sf::CircleShape circle(static_cast<float>(rx));
	circle.setFillColor(m_color);
	circle.setPosition(static_cast<float>(cx), static_cast<float>(cy));
	double scaleY = ry / rx;
	circle.setScale(1, static_cast<float>(scaleY));

	m_shapes.push_back(std::make_shared<sf::CircleShape>(circle));
}

void Canvas::DrawText(double left, double top, int fontSize, const std::string& text)
{
	sf::Text drawText;
	drawText.setPosition(static_cast<float>(left), static_cast<float>(top));
	drawText.setFont(m_font);
	drawText.setCharacterSize(fontSize);
	drawText.setString(text);
	drawText.setFillColor(m_color);

	m_shapes.push_back(std::make_shared<sf::Text>(drawText));
}

void Canvas::CanvasThread()
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 800), "Canvas");
	m_window->setVerticalSyncEnabled(true);
	m_window->setActive(false);

	while (m_window->isOpen())
	{
		sf::Event event;
		if (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}
		m_window->clear(sf::Color::White);
		for (int i = 0; i < m_shapes.size(); i++)
		{
			m_window->draw(*m_shapes[i]);
		}
		m_window->display();
	}

	return;
}
