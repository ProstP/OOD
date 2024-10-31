#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../lib/Adapter/ModernToOldGraphicsAdapter.h"
#include "../lib/Adapter/ModernToOldGraphicsAdapterClass.h"
#include "../lib/GraphicsLib/GraphicsLib.h"
#include "../lib/ModernGraphicsLib/ModernGraphicsLib.h"
#include "../lib/ModernGraphicsLib/ModernGraphicsLibv2.h"
#include "../lib/ShapeDrawingLib/ShapeDrawingLib.h"
#include <iostream>
#include <sstream>

TEST_CASE("Use adapter like ICanvas")
{
	WHEN("To draw triange")
	{
		std::stringstream out;
		{
			using namespace shape_drawing_lib;

			modern_graphics_lib::CModernGraphicsRenderer render(out);
			render.BeginDraw();
			Adapter::ModernToOldGraphicsAdapter adapter(render);
			CCanvasPainter painter(adapter);
			CTriangle triangle(Point{ 11, 12 }, Point{ 21, 22 }, Point{ 31, 32 }, 0x00ff11);
			painter.Draw(triangle);
		}

		std::string expected = "<draw>\n";
		expected += "  <line fromX=\"11\" fromY=\"12\" toX=\"21\" toY=\"22\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"21\" fromY=\"22\" toX=\"31\" toY=\"32\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"31\" fromY=\"32\" toX=\"11\" toY=\"12\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
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
			using namespace shape_drawing_lib;

			modern_graphics_lib::CModernGraphicsRenderer render(out);
			render.BeginDraw();
			Adapter::ModernToOldGraphicsAdapter adapter(render);
			CCanvasPainter painter(adapter);
			CRectangle rectangle(Point{ 10, 20 }, 5, 10, 0x100f50);
			painter.Draw(rectangle);
		}

		std::string expected = "<draw>\n";
		expected += "  <line fromX=\"10\" fromY=\"20\" toX=\"15\" toY=\"20\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"15\" fromY=\"20\" toX=\"15\" toY=\"30\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"15\" fromY=\"30\" toX=\"10\" toY=\"30\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"10\" fromY=\"30\" toX=\"10\" toY=\"20\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "</draw>\n";

		THEN("Out has params of rectangle")
		{
			CHECK(out.str() == expected);
		}
	}
}

TEST_CASE("Use adapter class like ICanvas")
{
	WHEN("To draw triange")
	{
		std::stringstream out;
		{
			using namespace shape_drawing_lib;

			Adapter::ModernToOLdGraphicsAdapterClass adapter(out);
			CCanvasPainter painter(adapter);
			CTriangle triangle(Point{ 11, 12 }, Point{ 21, 22 }, Point{ 31, 32 }, 0x00ff11);
			painter.Draw(triangle);
		}

		std::string expected = "<draw>\n";
		expected += "  <line fromX=\"11\" fromY=\"12\" toX=\"21\" toY=\"22\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"21\" fromY=\"22\" toX=\"31\" toY=\"32\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"31\" fromY=\"32\" toX=\"11\" toY=\"12\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
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
			using namespace shape_drawing_lib;

			Adapter::ModernToOLdGraphicsAdapterClass adapter(out);
			CCanvasPainter painter(adapter);
			CRectangle rectangle(Point{ 10, 20 }, 5, 10, 0x100f50);
			painter.Draw(rectangle);
		}

		std::string expected = "<draw>\n";
		expected += "  <line fromX=\"10\" fromY=\"20\" toX=\"15\" toY=\"20\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"15\" fromY=\"20\" toX=\"15\" toY=\"30\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"15\" fromY=\"30\" toX=\"10\" toY=\"30\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"10\" fromY=\"30\" toX=\"10\" toY=\"20\">\n";
		expected += "    <color r=\"0.06\" g=\"0.06\" b=\"0.31\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "</draw>\n";

		THEN("Out has params of rectangle")
		{
			CHECK(out.str() == expected);
		}
	}
	WHEN("Use child of ModernLib")
	{
		std::stringstream out;
		{
			using namespace shape_drawing_lib;

			Adapter::ModernToOLdGraphicsAdapterClass<modern_graphics_lib_v2::ModernGraphicsRenderv2> adapter(out);
			CCanvasPainter painter(adapter);
			CTriangle triangle(Point{ 11, 12 }, Point{ 21, 22 }, Point{ 31, 32 }, 0x00ff11);
			painter.Draw(triangle);
		}

		std::string expected = "<new draw>\n";
		expected += "  <line fromX=\"11\" fromY=\"12\" toX=\"21\" toY=\"22\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"21\" fromY=\"22\" toX=\"31\" toY=\"32\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "  <line fromX=\"31\" fromY=\"32\" toX=\"11\" toY=\"12\">\n";
		expected += "    <color r=\"0.00\" g=\"1.00\" b=\"0.07\" a=\"1.00\" />\n";
		expected += "  </line>\n";
		expected += "</new draw>\n";

		THEN("Out has params of triangle")
		{
			CHECK(out.str() == expected);
		}
	}
}
