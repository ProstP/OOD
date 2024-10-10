#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SfmlCanvas
{

class WindowCanvas
{
public:
	WindowCanvas();
	void DisplayShapes(const std::vector<std::shared_ptr<sf::Drawable>>& shapes);

private:
	sf::RenderWindow m_window;
};

} // namespace SfmlCanvas
