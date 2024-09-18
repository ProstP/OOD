#include "lib/CommandHandler/CommandHandler.h"
#include "lib/Sfml/Canvas.h"
#include "lib/Shapes/Picture.h"
#include "lib/WindowCanvas/WindowCanvas.h"
#include <iostream>

int main()
{
	Picture picture;
	WindowCanvas window;
	Canvas canvas(&window);
	picture.SetCanvas(&canvas);
	CommandHandler handler(&picture);

	handler.Handle(std::cin, std::cout);
}
