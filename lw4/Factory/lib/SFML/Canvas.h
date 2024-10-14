#pragma once
#include "../Canvas/ICanvas.h"
#include "../Shapes/Color.h"
#include "../Shapes/Point.h"
#include "WindowCanvas.h"

namespace SfmlCanvas
{

class SfmlCanvas : public Canvas::ICanvas
{
public:
	SfmlCanvas(std::unique_ptr<WindowCanvas>&& window)
		: m_window(std::move(window))
		, m_color(sf::Color::Black){};

	void DrawLine(const Shapes::Point& start, const Shapes::Point& end) override;
	void DrawEllipse(const Shapes::Point& center, double hr, double vr) override;
	void SetColor(Shapes::Color color) override;

	~SfmlCanvas() override = default;

private:
	std::unique_ptr<WindowCanvas> m_window;
	sf::Color m_color;
	std::vector<std::shared_ptr<sf::Drawable>> m_shapes;
};

} // namespace SfmlCanvas
