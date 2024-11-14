#include "../lib/CommandHandler/CommandHandler.h"
#include "../lib/Shape/Shapes.h"
#include <iostream>
#include "../lib/GraphicCanvas/Canvas.h"

int main()
{
	Shapes::Slide slide(800, 800);

	GraphicLib::GraphicCanvas canvas;
	CommandHandler handler(canvas, slide);

	handler.Handle(std::cin, std::cout);
}
