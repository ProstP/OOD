#pragma once
#include "../Shapes/Picture.h"
#include <iostream>

class CommandHandler
{
public:
	CommandHandler(Picture& picture);
	void Handle(std::istream& in, std::ostream& out);
	~CommandHandler();

private:
	Picture* m_picture;
};
