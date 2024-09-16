#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Shapes/lib/Gfx/Color.h"

TEST_CASE("Test with color")
{
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
}