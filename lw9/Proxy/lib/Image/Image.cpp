#include "Image.h"
#include <iostream>
#include <sstream>
#include <string>

Image::Image(Size size, char color)
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

char Image::GetPixel(Point p) const noexcept
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

void Image::SetPixel(Point p, char color)
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
