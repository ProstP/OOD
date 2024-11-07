#include "../lib/CommandHandler/CommandHandler.h"
#include "../lib/Shape/Shapes.h"
#include <iostream>
#include "../lib/OutstreamCanvas/OutstreamCanvas.h"

int main()
{
	Shapes::Slide slide(800, 800);
	OutstreamCanvas::OutstreamCanvas canvas(std::cout);
	CommandHandler handler(canvas, slide);

	handler.Handle(std::cin, std::cout);
}
