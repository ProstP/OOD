#include "CommandsToMenuCreator.h"
#include "../FileUtils/FileUtils.h"
#include "../RandStringGenerator/RandStringGenerator.h"

void CommandsToMenuCreator::AddCommands(Menu::Menu& menu, Document::IDocument& document)
{
	AddInsertParagraphCommand(menu, document);
	AddInsertImageCommand(menu, document);
	AddSetTitleCommand(menu, document);
	AddListCommand(menu, document);
	AddReplaceParagraphCommand(menu, document);
	AddResizeImageCommand(menu, document);
	AddDeleteItemCommand(menu, document);
	AddUndoCommand(menu, document);
	AddRedoCommand(menu, document);
	AddSaveCommand(menu, document);
	AddHelpCommand(menu);
	AddExitCommand(menu);
}

void CommandsToMenuCreator::AddInsertParagraphCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("InsertParagraph", "InsertParagraph <pos>|end <text>", [&document](std::istream& in) {
		std::string posStr;
		std::string text;
		in >> posStr;
		in >> text;

		try
		{
			int pos = std::stoi(posStr);

			document.InsertParagraph(text, pos);
		}
		catch (...)
		{
			document.InsertParagraph(text);
		}
	});
}

void CommandsToMenuCreator::AddInsertImageCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("InsertImage", "InsertImage <pos>|end <width> <height> <path>", [&document](std::istream& in) {
		std::string posStr;
		std::string widthStr;
		std::string heightStr;
		std::string path;
		in >> posStr;
		in >> widthStr;
		in >> heightStr;
		in >> path;

		const size_t length = 15;
		std::string newPath = "images/" + GenerateRandomString(length) + ".png";
		FileUtils::CopyFiles(path, newPath);

		int width;
		int height;
		try
		{
			width = std::stoi(widthStr);
			height = std::stoi(heightStr);
		}
		catch (...)
		{
			throw std::invalid_argument("Width and height of image are digits");
		}

		try
		{
			int pos = std::stoi(posStr);

			document.InsertImage(newPath, width, height, pos);
		}
		catch (...)
		{
			document.InsertImage(newPath, width, height);
		}
	});
}

void CommandsToMenuCreator::AddSetTitleCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("SetTitle", "SetTitle <title>", [&document](std::istream& in) {
		std::string title;
		in >> title;

		document.SetTitle(title);
	});
}

void CommandsToMenuCreator::AddListCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("List", "List", [&document](std::istream& in) {
		std::cout << "<------->" << std::endl;
		std::cout << "Title: " << document.GetTitle() << std::endl;
		for (int i = 0; i < document.GetItemCount(); i++)
		{
			std::cout << i << ":";

			auto item = document.GetItem(i);
			if (item.GetParagraph() != nullptr)
			{
				std::cout << item.GetParagraph()->GetText();
			}
			else if (item.GetImage() != nullptr)
			{
				std::cout << item.GetImage()->GetWidth() << " " << item.GetImage()->GetHeight() << " " << item.GetImage()->GetPath();
			}

			std::cout << std::endl;
		}
		std::cout << "<------->" << std::endl;
	});
}

void CommandsToMenuCreator::AddReplaceParagraphCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("ReplaceText", "ReplaceText <pos> <text>", [&document](std::istream& in) {
		int pos;
		std::string text;
		in >> pos;
		in >> text;

		auto item = document.GetItem(pos);

		if (item.GetParagraph() == nullptr)
		{
			throw std::invalid_argument("Item not paragraph");
		}

		item.GetParagraph()->SetText(text);
	});
}

void CommandsToMenuCreator::AddResizeImageCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("ResizeImage", "ResizeImage  <pos> <text>", [&document](std::istream& in) {
		int pos;
		int width;
		int height;
		in >> pos;
		in >> width;
		in >> height;

		auto item = document.GetItem(pos);

		if (item.GetImage() == nullptr)
		{
			throw std::invalid_argument("Item not image");
		}

		item.GetImage()->Resize(width, height);
	});
}

void CommandsToMenuCreator::AddDeleteItemCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("DeleteItem", "DeleteItem  <pos>", [&document](std::istream& in) {
		int pos;
		in >> pos;

		document.DeleteItem(pos);
	});
}

void CommandsToMenuCreator::AddUndoCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("Undo", "Undo", [&document](std::istream& in) {
		if (document.CanUndo())
		{
			document.Undo();
		}
	});
}

void CommandsToMenuCreator::AddRedoCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("Redo", "Redo", [&document](std::istream& in) {
		if (document.CanRedo())
		{
			document.Redo();
		}
	});
}

void CommandsToMenuCreator::AddSaveCommand(Menu::Menu& menu, Document::IDocument& document)
{
	menu.AddItem("Save", "Save <path>", [&document](std::istream& in) {
		std::string path;
		in >> path;

		document.Save(path);
	});
}

void CommandsToMenuCreator::AddHelpCommand(Menu::Menu& menu)
{
	menu.AddItem("Help", "Help", [&menu](std::istream& in) {
		menu.ShowInstructions();
	});
}

void CommandsToMenuCreator::AddExitCommand(Menu::Menu& menu)
{
	menu.AddItem("Exit", "Exit", [&menu](std::istream& in) {
		menu.Exit();
	});
}
