#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class WindowCanvas
{
public:
	WindowCanvas();
	void DisplayShapes(std::vector<std::shared_ptr<sf::Drawable>> figures);

private:
	sf::RenderWindow m_window;
};
