#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
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
