#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/Image/Image.h"
#include "../lib/Image/Tile.h"
#include <iostream>

bool CheckPixelsColorInTileToEqualSomeColor(const Tile& tile, char color)
{
	for (int x = 0; x < tile.SIZE; x++)
	{
		for (int y = 0; y < tile.SIZE; y++)
		{
			if (tile.GetPixel({ x, y }) != color)
			{
				return false;
			}
		}
	}

	return true;
}

TEST_CASE("Tile Initial")
{
	WHEN("Color some value")
	{
		char color = '@';
		Tile tile(color);

		THEN("All pixels color == value")
		{
			CHECK(CheckPixelsColorInTileToEqualSomeColor(tile, color));
			CHECK(tile.GetInstanceCount() == 1);
		}
	}
	WHEN("Without param")
	{
		Tile tile;

		THEN("All pixels color == space")
		{
			CHECK(CheckPixelsColorInTileToEqualSomeColor(tile, ' '));
			CHECK(tile.GetInstanceCount() == 1);
		}
	}
}

TEST_CASE("Tile GetColor")
{
	char color = '@';
	Tile tile(color);

	WHEN("x = SIZE")
	{
		THEN("Retern space")
		{
			CHECK(tile.GetPixel({ tile.SIZE, 0 }) == ' ');
		}
	}
	WHEN("y = SIZE")
	{
		THEN("Retern space")
		{
			CHECK(tile.GetPixel({ 0, tile.SIZE }) == ' ');
		}
	}
	WHEN("x > SIZE")
	{
		THEN("Retern space")
		{
			CHECK(tile.GetPixel({ tile.SIZE + 1, 0 }) == ' ');
		}
	}
	WHEN("y > SIZE")
	{
		THEN("Retern space")
		{
			CHECK(tile.GetPixel({ 0, tile.SIZE + 1 }) == ' ');
		}
	}
	WHEN("x and y < SIZE")
	{
		THEN("Return color")
		{
			CHECK(tile.GetPixel({ 2, 4 }) == color);
		}
	}
}

TEST_CASE("Tile SetPixel")
{
	const char baseColor = '@';
	const char anotherColor = '%';
	Tile tile(baseColor);

	WHEN("Set x = SIZE")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(tile.SetPixel(Point{ tile.SIZE, 0 }, anotherColor));
			CHECK(CheckPixelsColorInTileToEqualSomeColor(tile, baseColor));
		}
	}
	WHEN("Set y = SIZE")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(tile.SetPixel(Point{ 0, tile.SIZE }, anotherColor));
			CHECK(CheckPixelsColorInTileToEqualSomeColor(tile, baseColor));
		}
	}
	WHEN("Set x > SIZE")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(tile.SetPixel(Point{ tile.SIZE + 1, 0 }, anotherColor));
			CHECK(CheckPixelsColorInTileToEqualSomeColor(tile, baseColor));
		}
	}
	WHEN("Set y > SIZE")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(tile.SetPixel(Point{ 0, tile.SIZE + 1 }, anotherColor));
			CHECK(CheckPixelsColorInTileToEqualSomeColor(tile, baseColor));
		}
	}
	WHEN("x and y < SIZE")
	{
		Point pixel{ 2, 3 };

		auto checkThatOnlySettedPixelChange = [baseColor, anotherColor, pixel](const Tile& tile) {
			for (int x = 0; x < tile.SIZE; x++)
			{
				for (int y = 0; y < tile.SIZE; y++)
				{
					char colorToEqual = x == pixel.x && y == pixel.y ? anotherColor : baseColor;

					if (tile.GetPixel({ x, y }) != colorToEqual)
					{
						return false;
					}
				}
			}

			return true;
		};

		THEN("Pixel change color")
		{
			CHECK_NOTHROW(tile.SetPixel(pixel, anotherColor));
			CHECK(checkThatOnlySettedPixelChange(tile));
		}
	}
}

TEST_CASE("Tile Copy constuctor")
{
	WHEN("Create copy of tile")
	{
		const char baseColor = '@';

		Tile original(baseColor);
		Tile copy(original);

		auto checkTilesAreEqual = [](const Tile& first, const Tile& second) {
			for (int x = 0; x < first.SIZE; x++)
			{
				for (int y = 0; y < second.SIZE; y++)
				{
					if (first.GetPixel({ x, y }) != second.GetPixel({ x, y }))
					{
						return false;
					}
				}
			}

			return true;
		};

		THEN("Copy = original")
		{
			CHECK(checkTilesAreEqual(original, copy));
			CHECK(original.GetInstanceCount() == 2);
			CHECK(copy.GetInstanceCount() == 2);
		}
	}
	WHEN("Edit original and copy")
	{
		const char baseColor = '@';
		const char anotherColor = '%';

		Tile original(baseColor);
		Tile copy(original);

		Point inOriginal = { 1, 2 };
		Point inCopy = { 5, 6 };

		original.SetPixel(inOriginal, anotherColor);
		copy.SetPixel(inCopy, anotherColor);

		THEN("Changes in original not be in copy and vice versa")
		{
			CHECK(original.GetPixel(inOriginal) == anotherColor);
			CHECK(copy.GetPixel(inOriginal) == baseColor);
			CHECK(original.GetPixel(inCopy) == baseColor);
			CHECK(copy.GetPixel(inCopy) == anotherColor);
		}
	}
}

TEST_CASE("Image Inittial with not right params")
{
	WHEN("Negative width")
	{
		auto fn = []() {
			Image image(Size{ -1, 1 });
		};

		THEN("Exception")
		{
			CHECK_THROWS_AS(fn(), std::out_of_range);
		}
	}
	WHEN("Width = 0")
	{
		auto fn = []() {
			Image image(Size{ 0, 1 });
		};

		THEN("Exception")
		{
			CHECK_THROWS_AS(fn(), std::out_of_range);
		}
	}
	WHEN("Negative height")
	{
		auto fn = []() {
			Image image(Size{ 1, -1 });
		};

		THEN("Exception")
		{
			CHECK_THROWS_AS(fn(), std::out_of_range);
		}
	}
	WHEN("Height = 0")
	{
		auto fn = []() {
			Image image(Size{ 1, 0 });
		};

		THEN("Exception")
		{
			CHECK_THROWS_AS(fn(), std::out_of_range);
		}
	}
}

bool CheckPixelColorInImageToEqualForSomeColor(const Image& image, char color)
{
	for (int x = 0; x < image.GetSize().width; x++)
	{
		for (int y = 0; y < image.GetSize().height; y++)
		{
			if (image.GetPixel({ x, y }) != color)
			{
				return false;
			}
		}
	}

	return true;
}

TEST_CASE("Image Initial")
{
	WHEN("Without color")
	{
		Size size{ 24, 24 };
		Image image(size);
		THEN("Size will right")
		{
			CHECK(image.GetSize().width == size.width);
			CHECK(image.GetSize().height == size.height);
			CHECK(CheckPixelColorInImageToEqualForSomeColor(image, ' '));
		}
	}
	WHEN("With color")
	{
		char color = '@';
		Size size{ 24, 24 };
		Image image(size, color);
		THEN("Size will right")
		{
			CHECK(image.GetSize().width == size.width);
			CHECK(image.GetSize().height == size.height);
			CHECK(CheckPixelColorInImageToEqualForSomeColor(image, color));
		}
	}
}

TEST_CASE("Image tiles in initial")
{
	WHEN("Init image and check tile count")
	{
		Image image({ 64, 64 });

		THEN("Tile count = 1")
		{
			CHECK(Tile::GetInstanceCount() == 1);
		}
	}
}

TEST_CASE("Image GetPixel")
{
	const Size size{ 200, 200 };
	const char color = '@';
	const Image image(size, color);

	WHEN("x = width of image")
	{
		THEN("Return pixel with space")
		{
			CHECK(image.GetPixel({ size.width, 1 }) == ' ');
		}
	}
	WHEN("x > width of image")
	{
		THEN("Return pixel with space")
		{
			CHECK(image.GetPixel({ size.width + 1, 1 }) == ' ');
		}
	}
	WHEN("y = width of image")
	{
		THEN("Return pixel with space")
		{
			CHECK(image.GetPixel({ 1, size.height }) == ' ');
		}
	}
	WHEN("y > width of image")
	{
		THEN("Return pixel with space")
		{
			CHECK(image.GetPixel({ 1, size.height + 1 }) == ' ');
		}
	}
	WHEN("x and y < width and height of image")
	{
		THEN("Return pixel with color")
		{
			CHECK(image.GetPixel({ 1, 1 }) == color);
		}
	}
}

TEST_CASE("Image SetColor")
{
	const char baseColor = '@';
	const char anotherColor = '%';

	Size size{ 24, 24 };
	Image image(size, baseColor);

	WHEN("x = width of image")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(image.SetPixel({ size.width, 1 }, anotherColor));
			CHECK(Tile::GetInstanceCount() == 1);
		}
	}
	WHEN("y = height of image")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(image.SetPixel({ 1, size.height }, anotherColor));
			CHECK(Tile::GetInstanceCount() == 1);
		}
	}
	WHEN("x > width of image")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(image.SetPixel({ size.width + 1, 1 }, anotherColor));
			CHECK(Tile::GetInstanceCount() == 1);
		}
	}
	WHEN("y > height of image")
	{
		THEN("Nothing")
		{
			CHECK_NOTHROW(image.SetPixel({ 1, size.height + 1 }, anotherColor));
			CHECK(Tile::GetInstanceCount() == 1);
		}
	}
	WHEN("SetColor is right")
	{
		Point point{ 21, 16 };

		auto checkThatOnlyOnePixelChanged = [baseColor, anotherColor, point](const Image& image) {
			for (int x = 0; x < image.GetSize().width; x++)
			{
				for (int y = 0; y < image.GetSize().height; y++)
				{
					char colorToEqual = x == point.x && y == point.y ? anotherColor : baseColor;

					if (image.GetPixel({ x, y }) != colorToEqual)
					{
						return false;
					}
				}
			}

			return true;
		};

		THEN("Pixel in this position will has new color and tile count will 2")
		{
			CHECK_NOTHROW(image.SetPixel(point, anotherColor));
			CHECK(image.GetPixel(point) == anotherColor);
			CHECK(checkThatOnlyOnePixelChanged(image));
			CHECK(Tile::GetInstanceCount() == 2);
		}
	}
	WHEN("Double setColor in one tile")
	{
		Point point1{ 21, 14 };
		Point point2{ 18, 11 };

		THEN("Pixel in this position will has new color and tile count will 2")
		{
			CHECK_NOTHROW(image.SetPixel(point1, anotherColor));
			CHECK_NOTHROW(image.SetPixel(point2, anotherColor));
			CHECK(image.GetPixel(point1) == anotherColor);
			CHECK(image.GetPixel(point2) == anotherColor);
			CHECK(Tile::GetInstanceCount() == 2);
		}
	}
	WHEN("Double setColor in different tile")
	{
		Point point1{ 21, 14 };
		Point point2{ 2, 22 };

		THEN("Pixel in this position will has new color and tile count will 2")
		{
			CHECK_NOTHROW(image.SetPixel(point1, anotherColor));
			CHECK_NOTHROW(image.SetPixel(point2, anotherColor));
			CHECK(image.GetPixel(point1) == anotherColor);
			CHECK(image.GetPixel(point2) == anotherColor);
			CHECK(Tile::GetInstanceCount() == 3);
		}
	}
}
