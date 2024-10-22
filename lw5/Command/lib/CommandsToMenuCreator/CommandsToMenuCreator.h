#pragma once
#include "../DocumentCommands/DocumentCommands.h"
#include "../Menu/Menu.h"
#include "../MenuCommands/MenuCommands.h"
#include "../Document/IDocument.h"

class CommandsToMenuCreator
{
public:
	static void AddCommands(Menu::Menu& menu, Document::IDocument& document);

private:
	static void AddInsertParagraphCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddInsertImageCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddSetTitleCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddListCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddReplaceParagraphCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddResizeImageCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddDeleteItemCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddUndoCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddRedoCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddSaveCommand(Menu::Menu& menu, Document::IDocument& document);
	static void AddHelpCommand(Menu::Menu& menu);
	static void AddExitCommand(Menu::Menu& menu);
};
