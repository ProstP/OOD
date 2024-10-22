#include "../lib/CommandsToMenuCreator/CommandsToMenuCreator.h"
#include "../lib/ConcreteDocument/ConcreteDocument.h";
#include "../lib/Menu/Menu.h";
#include "../lib/FileUtils/FileUtils.h"
#include <iostream>

int main()
{
	FileUtils::CopyFiles("E:/ParallelProgramming/lw2/Lw2/Lw2/input.bmp", "out.bmp");

	/*
	ConcreteDocument::ConcreteDocument document;
	Menu::Menu menu;
	CommandsToMenuCreator::AddCommands(menu, document);

	menu.Run();
 */
}
