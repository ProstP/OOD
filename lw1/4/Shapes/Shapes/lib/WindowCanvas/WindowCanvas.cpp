#include "WindowCanvas.h"

WindowCanvas::WindowCanvas()
	: m_window(sf::VideoMode(1000, 800), "Window")
{
	m_window.setVerticalSyncEnabled(true);
}

void WindowCanvas::DrawShapes(std::vector<std::shared_ptr<sf::Drawable>> figures)
{
	m_window.clear(sf::Color::White);
	for (int i = 0; i < figures.size(); i++)
	{
		m_window.draw(*figures[i]);
	}
	m_window.display();
}

/*
std::shared_ptr<sf::RenderWindow> WindowCanvas::GetWindowRender()
{
	return m_window;
}

void WindowCanvas::WindowThread()
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 800), "Canvas");
	m_window->setVerticalSyncEnabled(true);
	m_window->setActive(false);
	m_window->clear(sf::Color::White);

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

		m_window->display();
	}
}
*/
