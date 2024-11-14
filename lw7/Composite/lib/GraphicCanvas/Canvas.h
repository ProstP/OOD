#pragma once
#include "../Canvas/ICanvas.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

namespace GraphicLib
{

class GraphicCanvas : public Canvas::ICanvas
{
public:
	void MoveTo(double x, double y) override
	{
		if (m_points.getVertexCount() == 2)
		{
			if (m_fillColor != std::nullopt)
			{
				m_points[0].color = m_fillColor.value();
				m_points[1].color = m_fillColor.value();
			}

			m_shapes.push_back(std::make_shared<sf::VertexArray>(m_points));
		}
		else if (m_points.getVertexCount() > 2)
		{
			CreateShapeFromPoints();
		}
		m_points = sf::VertexArray();

		m_points.append(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
	}
	void LineTo(double x, double y) override
	{
		if (m_points.getVertexCount() == 0)
		{
			m_points.append(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
			return;
		}

		sf::Vector2f position(static_cast<float>(x), static_cast<float>(y));
		if (m_points[0].position == position)
		{
			CreateShapeFromPoints();
		}

		m_points.append(position);
	}
	void SetOutlineColor(RGBAColor color) override
	{
		uint8_t a = color;
		uint8_t b = color >> 8;
		uint8_t g = color >> 16;
		uint8_t r = color >> 24;

		m_outlineColor = sf::Color(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
	}
	void ClearOutlineColor() override
	{
		m_outlineColor = std::nullopt;
	}
	void SetOutlineThickness(int thickness) override
	{
		m_thickness = thickness;
	}
	void DrawEllipse(double left, double top, double width, double height) override
	{
		sf::CircleShape circle(static_cast<float>(width / 2));
		circle.setPosition(static_cast<float>(left + width / 2), static_cast<float>(top + height / 2));
		double scaleY = (height / 2) / (width / 2);
		circle.setScale(1, static_cast<float>(scaleY));

		if (m_fillColor != std::nullopt)
		{
			circle.setFillColor(m_fillColor.value());
		}
		if (m_outlineColor != std::nullopt)
		{
			circle.setOutlineColor(m_outlineColor.value());
			circle.setOutlineThickness(static_cast<float>(m_thickness));
		}

		m_shapes.push_back(std::make_shared<sf::CircleShape>(circle));
	}
	void BeginFill(RGBAColor color) override
	{
		uint8_t a = color;
		uint8_t b = color >> 8;
		uint8_t g = color >> 16;
		uint8_t r = color >> 24;

		m_fillColor = sf::Color(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
	}
	void EndFill() override
	{
		m_fillColor = std::nullopt;
	}
	void SetBackgroundColor(RGBAColor color) override
	{
		uint8_t a = color;
		uint8_t b = color >> 8;
		uint8_t g = color >> 16;
		uint8_t r = color >> 24;

		m_backgroundColor = sf::Color(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
	}
	void Draw()
	{
		sf::RenderWindow window(sf::VideoMode(800, 800), "Window");
		window.setVerticalSyncEnabled(true);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

			window.clear(m_backgroundColor);

			for (auto shape : m_shapes)
			{
				window.draw(*shape);
			}

			window.display();
		}
	}

private:
	sf::Color m_backgroundColor = sf::Color::White;
	std::vector<std::shared_ptr<sf::Drawable>> m_shapes;
	std::optional<sf::Color> m_outlineColor = std::nullopt;
	std::optional<sf::Color> m_fillColor = std::nullopt;
	int m_thickness = 0;

	sf::VertexArray m_points;

	void CreateShapeFromPoints()
	{
		sf::ConvexShape shape(m_points.getVertexCount());

		for (size_t i = 0; i < m_points.getVertexCount(); i++)
		{
			shape.setPoint(i, m_points[i].position);
		}

		if (m_fillColor != std::nullopt)
		{
			shape.setFillColor(m_fillColor.value());
		}
		if (m_outlineColor != std::nullopt)
		{
			shape.setOutlineColor(m_outlineColor.value());
			shape.setOutlineThickness(static_cast<float>(m_thickness));
		}

		m_shapes.push_back(std::make_shared<sf::ConvexShape>(shape));

		m_points = sf::VertexArray();
	}
};

} // namespace GraphicLib
