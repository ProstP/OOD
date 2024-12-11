#include "CommandCreator.h"

void CommandCreator::AddCommands(Menu& menu, MultiGumballMachine& machine)
{
	AddFillCommand(menu, machine);
	AddEjectQuarterCommand(menu, machine);
	AddInsertQuarterCommand(menu, machine);
	AddTurnCrankCommand(menu, machine);
	AddInfoCommand(menu, machine);
	AddHelpCommand(menu);
	AddExitCommand(menu);
}

void CommandCreator::AddFillCommand(Menu& menu, MultiGumballMachine& machine)
{
	menu.AddItem("Fill", "Fill <count>", [&machine](std::istream& in) {
		unsigned count;
		// Проверка что вели count
		in >> count;

		try
		{
			machine.Fill(count);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	});
}

void CommandCreator::AddEjectQuarterCommand(Menu& menu, MultiGumballMachine& machine)
{
	menu.AddItem("EjectQuarter", "EjectQuarter", [&machine](std::istream& in) {
		machine.EjectQuarter();
	});
}

void CommandCreator::AddInsertQuarterCommand(Menu& menu, MultiGumballMachine& machine)
{
	menu.AddItem("InsertQuarter", "InsertQuarter", [&machine](std::istream& in) {
		machine.InsertQuarter();
	});
}

void CommandCreator::AddTurnCrankCommand(Menu& menu, MultiGumballMachine& machine)
{
	menu.AddItem("TurnCrank", "TurnCrank", [&machine](std::istream& in) {
		machine.TurnCrank();
	});
}

void CommandCreator::AddInfoCommand(Menu& menu, MultiGumballMachine& machine)
{
	menu.AddItem("Info", "Info", [&machine](std::istream& in) {
		std::cout << machine.ToString() << std::endl;
	});
}

void CommandCreator::AddHelpCommand(Menu& menu)
{
	menu.AddItem("Help", "Help", [&menu](std::istream& in) {
		menu.ShowInstructions();
	});
}

void CommandCreator::AddExitCommand(Menu& menu)
{
	menu.AddItem("Exit", "Exit", [&menu](std::istream& in) {
		menu.Exit();
	});
}
