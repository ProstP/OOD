#include "../lib/Client/Client.h"
#include "../lib/SFML/Canvas.h"
#include "../lib/SFML/WindowCanvas.h"
#include "../lib/SimpleDesigner/SimpleDesigner.h"
#include "../lib/SimplePainter/Painter.h"
#include "../lib/SimpleShapeFactory/SimpleShapeFactory.h"
#include <iostream>

int main()
{
	Client::Client c(std::make_unique<SfmlCanvas::SfmlCanvas>(std::make_unique<SfmlCanvas::WindowCanvas>()),
		std::make_unique<SimpleDesigner::SimpleDesigner>(std::make_unique<SimpleShapeFactory::SimpleShapeFactory>()),
		std::make_unique<SimplePainter::SimplePainter>());

	c.Run(std::cin, std::cout);
}
