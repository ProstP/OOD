#pragma once
#include "../Menu/Menu.h"
#include "../MultiGamBallMachine/MultiGamBallMachine.h"

using namespace MultiGumBallMachine;

class CommandCreator
{
public:
	static void AddCommands(Menu& menu, MultiGumballMachine& machine);

private:
	static void AddFillCommand(Menu& menu, MultiGumballMachine& machine);
	static void AddEjectQuarterCommand(Menu& menu, MultiGumballMachine& machine);
	static void AddInsertQuarterCommand(Menu& menu, MultiGumballMachine& machine);
	static void AddTurnCrankCommand(Menu& menu, MultiGumballMachine& machine);
	static void AddInfoCommand(Menu& menu, MultiGumballMachine& machine);
	static void AddHelpCommand(Menu& menu);
	static void AddExitCommand(Menu& menu);
};
