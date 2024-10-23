#include "../lib/CommandsToMenuCreator/CommandsToMenuCreator.h"
#include "../lib/ConcreteDocument/ConcreteDocument.h";
#include "../lib/Menu/Menu.h";
#include "../lib/FileUtils/FileUtils.h"
#include <iostream>

int main()
{
	//Пересмотреть удаление картинки
	//Однготиныее команды
	ConcreteDocument::ConcreteDocument document;
	Menu::Menu menu;
	CommandsToMenuCreator::AddCommands(menu, document);

	menu.Run();
}
