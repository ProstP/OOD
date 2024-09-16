#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Shapes/lib/DrawingStrategy/Imp/Circle/DrawCircle.h"
#include "../Shapes/lib/Gfx/Color.h"

TEST_CASE("Test with color")
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
		std::string hexColor = "ff0000";
		Color color(hexColor);

		THEN("R = 255, G = 0, B = 0")
		{
			CHECK(color.GetR() == 255);
			CHECK(color.GetG() == 0);
			CHECK(color.GetB() == 0);
		}
	}
	WHEN("Creating green")
	{
		std::string hexColor = "00ff00";
		Color color(hexColor);

		THEN("R = 0, G = 255, B = 0")
		{
			CHECK(color.GetR() == 0);
			CHECK(color.GetG() == 255);
			CHECK(color.GetB() == 0);
		}
	}
	WHEN("Creating blue")
	{
		std::string hexColor = "0000ff";
		Color color(hexColor);

		THEN("R = 0, G = 0, B = 255")
		{
			CHECK(color.GetR() == 0);
			CHECK(color.GetG() == 0);
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
