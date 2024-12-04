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

	// Возвращает количество экземпляра класса Tile в программе.
	static int GetInstanceCount() noexcept;

private:
	// -------------- не удалять ------------
	inline static int m_instanceCount = 0;
	// -------------- не удалять ------------

	std::vector<std::vector<uint32_t>> m_pixels;
};
