#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class WindowCanvas
{
public:
	WindowCanvas();
	void DrawShapes(std::vector<std::shared_ptr<sf::Drawable>> figures);

	//std::shared_ptr<sf::RenderWindow> GetWindowRender();

private:
	sf::RenderWindow m_window;
	//sf::Thread m_thread;
	//sf::Font m_font;
	//void WindowThread();
};
