#include "CommandHandler.h"

CommandHandler::CommandHandler(Picture& picture)
{
	*m_picture = picture;
}

void CommandHandler::Handle(std::istream& in, std::ostream& out)
{
}

CommandHandler::~CommandHandler()
{
	delete m_picture;
}
