#pragma once
#include "../Geom/Geom.h"
#include <cassert>
#include <vector>

class Tile
{
public:
	const static int SIZE = 8;

	Tile(uint32_t color = ' ');
	Tile(const Tile& other);

	~Tile();

	void SetPixel(Point p, uint32_t color);
	uint32_t GetPixel(Point p) const;

	// ���������� ���������� ���������� ������ Tile � ���������.
	static int GetInstanceCount() noexcept;

private:
	// -------------- �� ������� ------------
	inline static int m_instanceCount = 0;
	// -------------- �� ������� ------------

	std::vector<std::vector<uint32_t>> m_pixels;
};
