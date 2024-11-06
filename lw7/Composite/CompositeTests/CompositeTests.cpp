#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/OutstreamCanvas/OutstreamCanvas.h"
#include "../lib/Shape/Shapes.h"
#include "../lib/SimpleShapes/SimpleShapes.h"
#include <iostream>
#include <sstream>

TEST_CASE("Shape tests")
{
	WHEN("Fill and outline style is disable")
	{
		std::stringstream iss;
		OutstreamCanvas::OutstreamCanvas canvas(iss);

		SimpleShapes::Rectangle r;

		r.SetFrame({ 1, 1, 1, 1 });

		Shapes::Style style;
		style.Enable(false);
		r.SetFillStyle(style);

		Shapes::StyleWithThickness lineStyle;
		lineStyle.Enable(false);
		r.SetOutlineStyle(lineStyle);

		THEN("Exception")
		{
			CHECK_THROWS_WITH(r.Draw(canvas), "Shape is invisible");
		}
	}

	WHEN("Draw rectangle")
	{
		std::stringstream iss;
		OutstreamCanvas::OutstreamCanvas canvas(iss);

		SimpleShapes::Rectangle r;

		CommonTypes::RectD rect;
		rect.left = 10;
		rect.top = 15;
		rect.width = 10;
		rect.height = 15;
		r.SetFrame(rect);

		Shapes::Style style;
		style.Enable(true);
		style.SetColor(0x11223344);
		r.SetFillStyle(style);

		Shapes::StyleWithThickness lineStyle;
		lineStyle.Enable(true);
		lineStyle.SetColor(0x44332211);
		lineStyle.SetThickness(2);
		r.SetOutlineStyle(lineStyle);

		r.Draw(canvas);

		std::string expected = "Begin fill with color (#11223344)\n";
		expected += "Set color to outline (#44332211)\n";
		expected += "Thickness of outline is 2\n";
		expected += "Set pero to (10, 15)\n";
		expected += "Line to (20, 15)\n";
		expected += "Line to (20, 30)\n";
		expected += "Line to (10, 30)\n";
		expected += "Line to (10, 15)\n";
		expected += "Color of outline is cleared\n";
		expected += "End filling\n";

		THEN("Success draw")
		{
			CHECK(iss.str() == expected);
		}
	}

	WHEN("Draw triangle")
	{
		std::stringstream iss;
		OutstreamCanvas::OutstreamCanvas canvas(iss);

		SimpleShapes::Triangle t;

		CommonTypes::RectD rect;
		rect.left = 10;
		rect.top = 15;
		rect.width = 10;
		rect.height = 15;
		t.SetFrame(rect);

		Shapes::Style style;
		style.Enable(true);
		style.SetColor(0x11223344);
		t.SetFillStyle(style);

		Shapes::StyleWithThickness lineStyle;
		lineStyle.Enable(true);
		lineStyle.SetColor(0x44332211);
		lineStyle.SetThickness(2);
		t.SetOutlineStyle(lineStyle);

		t.Draw(canvas);

		std::string expected = "Begin fill with color (#11223344)\n";
		expected += "Set color to outline (#44332211)\n";
		expected += "Thickness of outline is 2\n";
		expected += "Set pero to (15, 15)\n";
		expected += "Line to (20, 30)\n";
		expected += "Line to (10, 30)\n";
		expected += "Line to (15, 15)\n";
		expected += "Color of outline is cleared\n";
		expected += "End filling\n";

		THEN("Success draw")
		{
			CHECK(iss.str() == expected);
		}
	}

	WHEN("Draw ellipse")
	{
		std::stringstream iss;
		OutstreamCanvas::OutstreamCanvas canvas(iss);

		SimpleShapes::Ellipse e;

		CommonTypes::RectD rect;
		rect.left = 10;
		rect.top = 15;
		rect.width = 10;
		rect.height = 15;
		e.SetFrame(rect);

		Shapes::Style style;
		style.Enable(true);
		style.SetColor(0x11223344);
		e.SetFillStyle(style);

		Shapes::StyleWithThickness lineStyle;
		lineStyle.Enable(true);
		lineStyle.SetColor(0x44332211);
		lineStyle.SetThickness(3);
		e.SetOutlineStyle(lineStyle);

		e.Draw(canvas);

		std::string expected = "Begin fill with color (#11223344)\n";
		expected += "Set color to outline (#44332211)\n";
		expected += "Thickness of outline is 3\n";
		expected += "Draw ellipse in fram left-top point (10, 15), width - 10, height - 15\n";
		expected += "Color of outline is cleared\n";
		expected += "End filling\n";

		THEN("Success draw")
		{
			CHECK(iss.str() == expected);
		}
	}
}

TEST_CASE("Group")
{
	WHEN("Add new shape out of frame")
	{
		Shapes::Group group;

		CommonTypes::RectD groupRect;
		groupRect.left = 10;
		groupRect.top = 15;
		groupRect.width = 10;
		groupRect.height = 15;
		group.SetFrame(groupRect);

		SimpleShapes::Rectangle rectangle1;
		CommonTypes::RectD rect1;
		rect1.left = 5;
		rect1.top = 5;
		rect1.width = 10;
		rect1.height = 10;
		rectangle1.SetFrame(rect1);
		SimpleShapes::Rectangle rectangle2;
		CommonTypes::RectD rect2;
		rect2.left = 10;
		rect2.top = 10;
		rect2.width = 30;
		rect2.height = 25;
		rectangle2.SetFrame(rect2);

		RectD expected1 = { 5, 5, 10, 15 };
		RectD expected2 = { 5, 5, 35, 25 };

		THEN("Frame will change")
		{
			CHECK_NOTHROW(group.InserShape(std::make_shared<SimpleShapes::Rectangle>(rectangle1), 0));
			CHECK(group.GetFrame().left == expected1.left);
			CHECK(group.GetFrame().top== expected1.top);
			CHECK(group.GetFrame().width == expected1.width);
			CHECK(group.GetFrame().height == expected1.height);
			CHECK_NOTHROW(group.InserShape(std::make_shared<SimpleShapes::Rectangle>(rectangle2), 0));
			CHECK(group.GetFrame().left == expected2.left);
			CHECK(group.GetFrame().top == expected2.top);
			CHECK(group.GetFrame().width == expected2.width);
			CHECK(group.GetFrame().height == expected2.height);
		}
	}
}
