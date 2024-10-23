#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/ConcreteDocument/ConcreteDocument.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

TEST_CASE("Paragraph")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Document is empty")
	{
		document.InsertParagraph("Text");

		THEN("Create paragraph")
		{
			CHECK(document.GetItem(0).GetParagraph()->GetText() == "Text");
			CHECK(document.GetItemCount() == 1);
		}
	}

	WHEN("New item will push from position")
	{
		document.InsertParagraph("Text0", std::nullopt);
		document.InsertParagraph("Text1", std::nullopt);
		document.InsertParagraph("Text2", std::nullopt);
		document.InsertParagraph("Text3", std::nullopt);

		document.InsertParagraph("AnotherText", 2);

		THEN("New Item will push another")
		{
			CHECK(document.GetItem(0).GetParagraph()->GetText() == "Text0");
			CHECK(document.GetItem(1).GetParagraph()->GetText() == "Text1");
			CHECK(document.GetItem(2).GetParagraph()->GetText() == "AnotherText");
			CHECK(document.GetItem(3).GetParagraph()->GetText() == "Text2");
			CHECK(document.GetItem(4).GetParagraph()->GetText() == "Text3");
		}
	}

	WHEN("Change text of paragraph")
	{
		document.InsertParagraph("Text0", std::nullopt);
		document.InsertParagraph("Text1", std::nullopt);

		document.GetItem(1).GetParagraph()->SetText("New Text");

		THEN("Change succesfull")
		{
			CHECK(document.GetItem(0).GetParagraph()->GetText() == "Text0");
			CHECK(document.GetItem(1).GetParagraph()->GetText() == "New Text");
		}
	}
}

TEST_CASE("Image")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Document is empty")
	{
		document.InsertImage("Test", 100, 200);

		THEN("Create image")
		{
			CHECK(document.GetItem(0).GetImage()->GetPath() == "Test");
			CHECK(document.GetItem(0).GetImage()->GetWidth() == 100);
			CHECK(document.GetItem(0).GetImage()->GetHeight() == 200);
			CHECK(document.GetItemCount() == 1);
		}
	}

	WHEN("New item will push from position")
	{
		document.InsertImage("Test0", 100, 200);
		document.InsertParagraph("Text1");
		document.InsertParagraph("Text2");
		document.InsertImage("Test3", 100, 200);

		document.InsertImage("AnotherPath", 200, 10, 2);

		THEN("New Item will push another")
		{
			CHECK(document.GetItem(0).GetImage()->GetPath() == "Test0");
			CHECK(document.GetItem(1).GetParagraph()->GetText() == "Text1");
			CHECK(document.GetItem(2).GetImage()->GetPath() == "AnotherPath");
			CHECK(document.GetItem(3).GetParagraph()->GetText() == "Text2");
			CHECK(document.GetItem(4).GetImage()->GetPath() == "Test3");
		}
	}
}

TEST_CASE("Deleting item")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Deleting paragraph")
	{
		document.InsertParagraph("Hello");
		document.InsertImage("Path", 1, 1);

		document.DeleteItem(0);

		THEN("Paragraph will deleting, image will be first")
		{
			CHECK(document.GetItemCount() == 1);
			CHECK(document.GetItem(0).GetImage()->GetPath() == "Path");
		}
	}
	WHEN("Deleting image")
	{
		document.InsertImage("Path", 1, 1);
		document.InsertParagraph("Hello");

		document.DeleteItem(0);

		THEN("Image will deleting, paragraph will be first")
		{
			CHECK(document.GetItemCount() == 1);
			CHECK(document.GetItem(0).GetParagraph()->GetText() == "Hello");
		}
	}
}

TEST_CASE("SetTitle")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Set new title")
	{
		document.SetTitle("Title");

		THEN("Title will be changed")
		{
			CHECK(document.GetTitle() == "Title");
			CHECK_NOTHROW(document.SetTitle("New Title"));
			CHECK(document.GetTitle() == "New Title");
		}
	}
}

TEST_CASE("Undo + Redo")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Set new title, undo and redo")
	{
		document.SetTitle("Title");

		THEN("Title not changed")
		{
			CHECK(document.GetTitle() == "Title");
			CHECK_NOTHROW(document.SetTitle("New Title"));
			CHECK(document.GetTitle() == "New Title");
			CHECK_NOTHROW(document.Undo());
			CHECK(document.GetTitle() == "Title");
			CHECK_NOTHROW(document.Redo());
			CHECK(document.GetTitle() == "New Title");
		}
	}

	WHEN("Undo and execute new command")
	{
		document.SetTitle("Title");

		THEN("Unexecute command will be removed")
		{
			CHECK(document.GetTitle() == "Title");
			CHECK_NOTHROW(document.SetTitle("New Title1"));
			CHECK_NOTHROW(document.SetTitle("New Title2"));
			CHECK(document.GetTitle() == "New Title2");
			CHECK_NOTHROW(document.Undo());
			CHECK_NOTHROW(document.Undo());
			CHECK_NOTHROW(document.SetTitle("Another Title"));
			CHECK(document.GetTitle() == "Another Title");
			CHECK_NOTHROW(document.Redo());
			CHECK_NOTHROW(document.Redo());
			CHECK(document.GetTitle() == "Another Title");
		}
	}
}

TEST_CASE("File with image")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Add image item, undo, delete command")
	{
		const std::string filePath = "image.png";
		std::ofstream out(filePath);
		out.close();

		document.InsertImage(filePath, 1, 1);
		THEN("File will delete when delete command")
		{
			CHECK(std::filesystem::exists(filePath));
			CHECK_NOTHROW(document.Undo());
			CHECK(std::filesystem::exists(filePath));
			CHECK_NOTHROW(document.SetTitle("New title"));
			CHECK(!std::filesystem::exists(filePath));
		}
	}
}
