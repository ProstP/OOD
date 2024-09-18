#include "WindowCanvas.h"

WindowCanvas::WindowCanvas()
	: m_thread(&WindowCanvas::WindowThread, this)
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 800), "Canvas");
	m_thread.launch();
}

std::shared_ptr<sf::RenderWindow> WindowCanvas::GetWindowRender()
{
	return m_window;
}

void WindowCanvas::WindowThread()
{
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

		m_window->display();
	}
}
