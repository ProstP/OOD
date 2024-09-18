#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class WindowCanvas
{
public:
	WindowCanvas();

	std::shared_ptr<sf::RenderWindow> GetWindowRender();

private:
	std::shared_ptr<sf::RenderWindow> m_window;
	sf::Thread m_thread;
	void WindowThread();
};
