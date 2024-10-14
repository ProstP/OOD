#include "WindowCanvas.h"

SfmlCanvas::WindowCanvas::WindowCanvas()
	: m_window(sf::VideoMode(1000, 800), "Window")
{
	m_window.setVerticalSyncEnabled(true);
}

void SfmlCanvas::WindowCanvas::DisplayShapes(const std::vector<std::shared_ptr<sf::Drawable>>& shapes)
{
	m_window.clear(sf::Color::White);

	for (int i = 0; i < shapes.size(); i++)
	{
		m_window.draw(*shapes[i]);
	}
	m_window.display();

	/*
	while (m_window.isOpen())
	{
		sf::Event e;
		if (m_window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

	}
	*/
}
