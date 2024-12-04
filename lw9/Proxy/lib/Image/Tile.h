#pragma once
#include "../Geom/Geom.h"
#include <cassert>
#include <vector>

class Tile
{
public:
	const static int SIZE = 8;

	Tile(char color = ' ');
	Tile(const Tile& other);

	~Tile();

	void SetPixel(Point p, char color);
	char GetPixel(Point p) const;

	// ���������� ���������� ���������� ������ Tile � ���������.
	static int GetInstanceCount() noexcept;

private:
	// -------------- �� ������� ------------
	inline static int m_instanceCount = 0;
	// -------------- �� ������� ------------

	std::vector<std::vector<char>> m_pixels;
};
