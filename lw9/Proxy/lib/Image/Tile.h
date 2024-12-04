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

	// Возвращает количество экземпляра класса Tile в программе.
	static int GetInstanceCount() noexcept;

private:
	// -------------- не удалять ------------
	inline static int m_instanceCount = 0;
	// -------------- не удалять ------------

	std::vector<std::vector<char>> m_pixels;
};
