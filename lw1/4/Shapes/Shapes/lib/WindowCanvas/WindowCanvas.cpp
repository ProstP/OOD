#include "WindowCanvas.h"

WindowCanvas::WindowCanvas()
	: m_window(sf::VideoMode(1000, 800), "Window")
{
	m_window.setVerticalSyncEnabled(true);
}

void WindowCanvas::DisplayShapes(std::vector<std::shared_ptr<sf::Drawable>> figures)
{
	m_window.clear(sf::Color::White);
	for (int i = 0; i < figures.size(); i++)
	{
		m_window.draw(*figures[i]);
	}
	m_window.display();
}
