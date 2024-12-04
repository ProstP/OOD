#include "Image.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Image::Image(Size size, uint32_t color)
{
	if (size.width <= 0 || size.height <= 0)
	{
		throw std::out_of_range("Size of image must be positive");
	}

	m_size = size;

	Tile tile(color);
	int width = size.width / tile.SIZE;
	width += size.width % tile.SIZE == 0 ? 0 : 1;
	int height = size.height / tile.SIZE;
	height += size.height % tile.SIZE == 0 ? 0 : 1;

	CoW<Tile> cow(tile);
	m_tiles = std::vector<std::vector<CoW<Tile>>>(width, std::vector<CoW<Tile>>(height, cow));
}

Size Image::GetSize() const noexcept
{
	return m_size;
}

uint32_t Image::GetPixel(Point p) const noexcept
{
	if (p.x >= m_size.width || p.y >= m_size.height)
	{
		return ' ';
	}

	int tileIndexX = p.x / Tile::SIZE;
	int pixelIndexX = p.x % Tile::SIZE;
	int tileIndexY = p.y / Tile::SIZE;
	int pixelIndexY = p.y % Tile::SIZE;

	return m_tiles[tileIndexX][tileIndexY]->GetPixel({ pixelIndexX, pixelIndexY });
}

void Image::SetPixel(Point p, uint32_t color)
{
	if (p.x >= m_size.width || p.y >= m_size.height)
	{
		return;
	}

	int tileIndexX = p.x / Tile::SIZE;
	int pixelIndexX = p.x % Tile::SIZE;
	int tileIndexY = p.y / Tile::SIZE;
	int pixelIndexY = p.y % Tile::SIZE;

	m_tiles[tileIndexX][tileIndexY].Write()->SetPixel({ pixelIndexX, pixelIndexY }, color);
}

void Print(const Image& img, std::ostream& out)
{
	const auto size = img.GetSize();
	for (int y = 0; y < size.height; ++y)
	{
		for (int x = 0; x < size.width; ++x)
		{
			out.put(img.GetPixel({ x, y }));
		}
		out.put('\n');
	}
}

Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (char ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}

void SaveImage(const Image& image, const std::string& fileName)
{
	std::ofstream file(fileName);

	file << "P3\n";

	file << image.GetSize().width << " " << image.GetSize().height << "\n";

	file << "255\n";

	for (int y = 0; y < image.GetSize().height; y++)
	{
		for (int x = 0; x < image.GetSize().width; x++)
		{
			uint32_t color = image.GetPixel({ x, y });

			uint8_t b = color;
			uint8_t g = color >> 8;
			uint8_t r = color >> 16;

			file << static_cast<int>(r) << " " << static_cast<int>(g) << " " << static_cast<int>(b) << "\n";
		}
	}
}
