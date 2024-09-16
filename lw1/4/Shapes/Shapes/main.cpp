#include "lib/CommandHandler/CommandHandler.h"
#include "lib/Shapes/Picture.h"
#include <iostream>

int main()
{
	Picture picture;
	CommandHandler handler(picture);

	handler.Handle(std::cin, std::cout);
}
