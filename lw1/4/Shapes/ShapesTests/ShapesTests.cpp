#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Shapes/lib/DrawingStrategy/Imp/Circle/DrawCircle.h"
#include "../Shapes/lib/DrawingStrategy/Imp/Line/DrawLine.h"
#include "../Shapes/lib/DrawingStrategy/Imp/Rectangle/DrawRectangle.h"
#include "../Shapes/lib/DrawingStrategy/Imp/Text/DrawText.h"
#include "../Shapes/lib/DrawingStrategy/Imp/Traingle/DrawTriangle.h"
#include "../Shapes/lib/Gfx/Color.h"

TEST_CASE("Color")
{
	WHEN("Creating with hex-length != 6")
	{
		auto fn = []() {
			Color color("dsadasdasdasda");
		};
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(fn(), "Hex length must be equal 6");
		}
	}
	WHEN("Creating red")
	{
		Color color("ff0000");

		THEN("R = 255, G = 0, B = 0")
		{
			CHECK(color.GetR() == 255);
			CHECK(color.GetG() == 0);
			CHECK(color.GetB() == 0);
		}
	}
	WHEN("Creating green")
	{
		Color color("00ff00");

		THEN("R = 0, G = 255, B = 0")
		{
			CHECK(color.GetR() == 0);
			CHECK(color.GetG() == 255);
			CHECK(color.GetB() == 0);
		}
	}
	WHEN("Creating blue")
	{
		Color color("0000ff");

		THEN("R = 0, G = 0, B = 255")
		{
			CHECK(color.GetR() == 0);
			CHECK(color.GetG() == 0);
			CHECK(color.GetB() == 255);
		}
	}
	WHEN("Create with str un upcase")
	{
		Color color("FFFFFF");

		THEN("All parametrs is 255")
		{
			CHECK(color.GetR() == 255);
			CHECK(color.GetG() == 255);
			CHECK(color.GetB() == 255);
		}
	}
	WHEN("Get hex from color")
	{
		std::string hex = "12ff98";
		Color color(hex);

		THEN("hex equal hex from color")
		{
			CHECK(color.GetInHex() == hex);
		}
	}
}

TEST_CASE("Circle")
{
	WHEN("Params invalid")
	{
		auto fn = []() {
			DrawCircle circle("dsdasda");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params not digit")
	{
		auto fn = []() {
			DrawCircle circle("12.22 . .");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params are digits")
	{
		std::string params = "12.22 22 22";
		DrawCircle circle(params);

		THEN("Params are right and type circle")
		{
			CHECK(circle.GetType() == "circle");
			CHECK(circle.GetParams() == params);
		}
	}
	WHEN("Move")
	{
		std::string params = "12.22 22 22";
		DrawCircle circle(params);
		circle.MoveTo(5.2, -2.3);
		std::string expected = "17.42 19.7 22";

		THEN("Params are change")
		{
			CHECK(circle.GetParams() == expected);
		}
	}
}

TEST_CASE("Rectangle")
{
	WHEN("Params invalid")
	{
		auto fn = []() {
			DrawRectangle rect("dsdasda");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params not digit")
	{
		auto fn = []() {
			DrawRectangle rect("12.22 . . 2.2.2");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params are digits")
	{
		std::string params = "12.22 22 22 11.22222";
		DrawRectangle rect(params);

		THEN("Params are right and type rectangle")
		{
			CHECK(rect.GetType() == "rectangle");
			CHECK(rect.GetParams() == params);
		}
	}
	WHEN("Move")
	{
		std::string params = "12.22 22 22 11.22222";
		DrawRectangle rect(params);
		rect.MoveTo(5.2, -2.3);
		std::string expected = "17.42 19.7 22 11.22222";

		THEN("Params are change")
		{
			CHECK(rect.GetParams() == expected);
		}
	}
}

TEST_CASE("Triangle")
{
	WHEN("Params invalid")
	{
		auto fn = []() {
			DrawTriangle tr("dsdasda");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params not digit")
	{
		auto fn = []() {
			DrawTriangle tr("12.22 . . 2.2.2 . 23");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params are digits")
	{
		std::string params = "12.22 22 22 11.2 2 0.23";
		DrawTriangle tr(params);

		THEN("Params are right and type triangle")
		{
			CHECK(tr.GetType() == "triangle");
			CHECK(tr.GetParams() == params);
		}
	}
	WHEN("Move")
	{
		std::string params = "12.22 22 22 11.2 2 12.3";
		DrawTriangle tr(params);
		tr.MoveTo(5.2, -2.3);
		std::string expected = "17.42 19.7 27.2 8.9 7.2 10";

		THEN("Params are change")
		{
			CHECK(tr.GetParams() == expected);
		}
	}
}

TEST_CASE("Line")
{
	WHEN("Params invalid")
	{
		auto fn = []() {
			DrawLine line("dsdasda");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params not digit")
	{
		auto fn = []() {
			DrawLine line("12.22 . . 2.2.2");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params are digits")
	{
		std::string params = "12.22 22 22 11.2";
		DrawLine line(params);

		THEN("Params are right and type line")
		{
			CHECK(line.GetType() == "line");
			CHECK(line.GetParams() == params);
		}
	}
	WHEN("Move")
	{
		std::string params = "12.22 22 22 11.2";
		DrawLine line(params);
		line.MoveTo(5.2, -2.3);
		std::string expected = "17.42 19.7 27.2 8.9";

		THEN("Params are change")
		{
			CHECK(line.GetParams() == expected);
		}
	}
}

TEST_CASE("Text")
{
	WHEN("Params invalid")
	{
		auto fn = []() {
			DrawTextStrategy text("dsdasda");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params not digit")
	{
		auto fn = []() {
			DrawTextStrategy text("12.22 . . Hello World!!!");
		};

		THEN("Will throw exception")
		{
			CHECK_THROWS_AS(fn(), std::invalid_argument);
		}
	}
	WHEN("Params are digits expect text")
	{
		std::string params = "12.22 22 22 Hello World!!!";
		DrawTextStrategy text(params);

		THEN("Params are right and type text")
		{
			CHECK(text.GetType() == "text");
			CHECK(text.GetParams() == params);
		}
	}
	WHEN("Move")
	{
		std::string params = "12.22 22 22 text";
		DrawTextStrategy line(params);
		line.MoveTo(5.2, -2.3);
		std::string expected = "17.42 19.7 22 text";

		THEN("Params are change")
		{
			CHECK(line.GetParams() == expected);
		}
	}
}
