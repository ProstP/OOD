#include "MenuCommands.h"

void MenuCommands::HelpCommand::Execute()
{
	m_menuPtr->Help();
}

void MenuCommands::ExitCommand::Execute()
{
	m_menuPtr->Exit();
}
