#include "Canvas.h"

void SfmlCanvas::SfmlCanvas::DrawLine(const Shapes::Point& start, const Shapes::Point& end)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].color = m_color;
	line[1].color = m_color;

	line[0].position = sf::Vector2f(static_cast<float>(start.x), static_cast<float>(start.y));
	line[1].position = sf::Vector2f(static_cast<float>(end.x), static_cast<float>(end.y));

	m_shapes.push_back(std::make_shared<sf::VertexArray>(line));
	m_window->DisplayShapes(m_shapes);
}

void SfmlCanvas::SfmlCanvas::DrawEllipse(const Shapes::Point& center, double hr, double vr)
{
	sf::CircleShape circle(static_cast<float>(hr));
	circle.setFillColor(m_color);
	circle.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));
	double scaleY = vr / hr;
	circle.setScale(1, static_cast<float>(scaleY));

	m_shapes.push_back(std::make_shared<sf::CircleShape>(circle));
	m_window->DisplayShapes(m_shapes);
}

void SfmlCanvas::SfmlCanvas::SetColor(Shapes::Color color)
{
	switch (color)
	{
	case Shapes::Color::Red:
		m_color = sf::Color::Red;
		break;
	case Shapes::Color::Green:
		m_color = sf::Color::Green;
		break;
	case Shapes::Color::Blue:
		m_color = sf::Color::Blue;
		break;
	case Shapes::Color::Pink:
		m_color = sf::Color(255, 192, 203);
		break;
	case Shapes::Color::Yellow:
		m_color = sf::Color::Yellow;
		break;
	case Shapes::Color::Black:
		m_color = sf::Color::Black;
		break;
	default:
		throw std::invalid_argument("Uknown color");
	}
}
