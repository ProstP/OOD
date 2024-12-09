#include "../lib/CommandCreator/CommandCreator.h"
#include "../lib/GamBallMachine/GumBallMachine.h"
#include "../lib/Menu/Menu.h"
#include <iostream>

using namespace GamBallMachine;

int main()
{
	MultiGumballMachine machine(5);
	Menu menu;
	CommandCreator::AddCommands(menu, machine);

	menu.Run();
}
