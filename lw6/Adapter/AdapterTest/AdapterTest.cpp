#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../lib/Adapter/ModernToOldGraphicsAdapter.h"
#include "../lib/GraphicsLib/GraphicsLib.h"
#include "../lib/ModernGraphicsLib/ModernGraphicsLib.h"
#include "../lib/ShapeDrawingLib/ShapeDrawingLib.h"
#include <iostream>
#include <sstream>

TEST_CASE("Using BeginDraw and EndDraw by adapter")
{
	WHEN("Add graphics render to adapter")
	{
		modern_graphics_lib::CModernGraphicsRenderer render(std::cout);
		Adapter::ModernToOldGraphicsAdapter adapter(render);

		THEN("Adapter begin drawing")
		{
			CHECK_THROWS_WITH(render.BeginDraw(), "Drawing has already begun");
		}
	}

	WHEN("Destroy adapter")
	{
		modern_graphics_lib::CModernGraphicsRenderer render(std::cout);
		{
			Adapter::ModernToOldGraphicsAdapter adapter(render);
		}

		THEN("Adapter end drawing")
		{
			CHECK_THROWS_WITH(render.EndDraw(), "Drawing has not been started");
		}
	}
}

TEST_CASE("Use adapter like ICanvas")
{
	WHEN("To draw triange")
	{
		std::stringstream out;
		{
			modern_graphics_lib::CModernGraphicsRenderer render(out);
			Adapter::ModernToOldGraphicsAdapter adapter(render);
			shape_drawing_lib::CCanvasPainter painter(adapter);
			shape_drawing_lib::CTriangle triangle(shape_drawing_lib::Point{ 11, 12 }, shape_drawing_lib::Point{ 21, 22 }, shape_drawing_lib::Point{ 31, 32 });
			painter.Draw(triangle);
		}

		std::string expected = "<draw>\n";
		expected += "  <line fromX=\"11\" fromY=\"12\" toX=\"21\" toY=\"22\"/>\n";
		expected += "  <line fromX=\"21\" fromY=\"22\" toX=\"31\" toY=\"32\"/>\n";
		expected += "  <line fromX=\"31\" fromY=\"32\" toX=\"11\" toY=\"12\"/>\n";
		expected += "</draw>\n";

		THEN("Out has params of triangle")
		{
			CHECK(out.str() == expected);
		}
	}
	WHEN("To draw rectangle")
	{
		std::stringstream out;
		{
			modern_graphics_lib::CModernGraphicsRenderer render(out);
			Adapter::ModernToOldGraphicsAdapter adapter(render);
			shape_drawing_lib::CCanvasPainter painter(adapter);
			shape_drawing_lib::CRectangle rectangle(shape_drawing_lib::Point{ 10, 20 }, 5, 10);
			painter.Draw(rectangle);
		}

		std::string expected = "<draw>\n";
		expected += "  <line fromX=\"10\" fromY=\"20\" toX=\"15\" toY=\"20\"/>\n";
		expected += "  <line fromX=\"15\" fromY=\"20\" toX=\"15\" toY=\"30\"/>\n";
		expected += "  <line fromX=\"15\" fromY=\"30\" toX=\"10\" toY=\"30\"/>\n";
		expected += "  <line fromX=\"10\" fromY=\"30\" toX=\"10\" toY=\"20\"/>\n";
		expected += "</draw>\n";

		THEN("Out has params of rectangle")
		{
			CHECK(out.str() == expected);
		}
	}
}
