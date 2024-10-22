#include "MenuCommands.h"

void MenuCommands::HelpCommand::Execute()
{
	m_menuPtr->ShowInstructions();
}

void MenuCommands::ExitCommand::Execute()
{
	m_menuPtr->Exit();
}
