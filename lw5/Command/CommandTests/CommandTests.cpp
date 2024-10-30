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
		document.InsertParagraph("Text0");
		document.InsertParagraph("Text1");
		document.InsertParagraph("Text2");
		document.InsertParagraph("Text3");

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
			CHECK_NOTHROW(document.Redo());
			CHECK_NOTHROW(document.Undo());
			CHECK(std::filesystem::exists(filePath));
			CHECK_NOTHROW(document.SetTitle("New title"));
			CHECK(!std::filesystem::exists(filePath));
		}
	}
}

TEST_CASE("History has 10 command")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Execute 11 command")
	{
		for (int i = 0; i < 11; i++)
		{
			document.InsertParagraph(std::to_string(i));
		}

		THEN("Can't undo first command")
		{
			CHECK(document.GetItemCount() == 11);

			for (int i = 0; i < 11; i++)
			{
				document.Undo();
			}

			CHECK(document.GetItemCount() == 1);
		}
	}

	WHEN("Delete command to delete image")
	{
		const std::string filePath = "image.png";
		std::ofstream out(filePath);
		out.close();

		document.InsertImage(filePath, 1, 1);

		THEN("file will delete")
		{
			CHECK(std::filesystem::exists(filePath));
			CHECK_NOTHROW(document.DeleteItem(0));
			CHECK(std::filesystem::exists(filePath));

			for (int i = 0; i < 10; i++)
			{
				document.SetTitle(std::to_string(i));
			}

			CHECK(!std::filesystem::exists(filePath));
		}
	}
}

TEST_CASE("Replace text in paragraph")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Replace text, undo, redo")
	{
		document.InsertParagraph("hello");
		document.GetItem(0).GetParagraph()->SetText("new text");

		THEN("Text will changed")
		{
			CHECK(document.GetItem(0).GetParagraph()->GetText() == "new text");
			CHECK_NOTHROW(document.Undo());
			CHECK(document.GetItem(0).GetParagraph()->GetText() == "hello");
			CHECK_NOTHROW(document.Redo());
			CHECK(document.GetItem(0).GetParagraph()->GetText() == "new text");
		}
	}
}

TEST_CASE("Resize image")
{
	ConcreteDocument::ConcreteDocument document;

	WHEN("Resize image, undo, redo")
	{
		document.InsertImage("path", 1, 2);
		document.GetItem(0).GetImage()->Resize(11, 12);

		THEN("Text will changed")
		{
			CHECK(document.GetItem(0).GetImage()->GetWidth() == 11);
			CHECK(document.GetItem(0).GetImage()->GetHeight() == 12);
			CHECK_NOTHROW(document.Undo());
			CHECK(document.GetItem(0).GetImage()->GetWidth() == 1);
			CHECK(document.GetItem(0).GetImage()->GetHeight() == 2);
			CHECK_NOTHROW(document.Redo());
			CHECK(document.GetItem(0).GetImage()->GetWidth() == 11);
			CHECK(document.GetItem(0).GetImage()->GetHeight() == 12);
		}
	}
}
