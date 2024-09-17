#include "lib/CommandHandler/CommandHandler.h"
#include "lib/Shapes/Picture.h"
#include <iostream>
#include "../SFML/Canvas.h"

int main()
{
	Picture picture;
	Canvas canvas;
	picture.SetCanvas(&canvas);
	CommandHandler handler(&picture);

	handler.Handle(std::cin, std::cout);
}
