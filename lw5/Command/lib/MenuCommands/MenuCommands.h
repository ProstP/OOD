#pragma once
#include "../Command/ICommand.h"
#include "../Menu/Menu.h"

namespace MenuCommands
{

class HelpCommand : public Command::ICommand
{
public:
	HelpCommand(Menu::Menu& menu)
		: m_menuPtr(&menu){};

	void Execute() override;

private:
	Menu::Menu* m_menuPtr;
};

class ExitCommand : public Command::ICommand
{
public:
	ExitCommand(Menu::Menu& menu)
		: m_menuPtr(&menu) {};

	void Execute() override;

private:
	Menu::Menu* m_menuPtr;
};

} // namespace MenuCommand
