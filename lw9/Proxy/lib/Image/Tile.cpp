#include "Tile.h"

Tile::Tile(char color)
{
	m_pixels = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, color));

	// -------------- не удалять ------------
	assert(m_instanceCount >= 0);
	++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
	// -------------- не удалять ------------
}

Tile::Tile(const Tile& other)
{
	m_pixels = other.m_pixels;

	// -------------- не удалять ------------
	assert(m_instanceCount >= 0);
	++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
	// -------------- не удалять ------------
}

Tile::~Tile()
{
	// -------------- не удалять ------------
	--m_instanceCount; // Уменьшаем счётчик тайлов.
	assert(m_instanceCount >= 0);
	// -------------- не удалять ------------
}

void Tile::SetPixel(Point p, char color)
{
	if (p.x >= SIZE || p.y >= SIZE)
	{
		return;
	}

	m_pixels[p.x][p.y] = color;
}

char Tile::GetPixel(Point p) const
{
	if (p.x >= SIZE || p.y >= SIZE)
	{
		return ' ';
	}

	return m_pixels[p.x][p.y];
}

int Tile::GetInstanceCount() noexcept
{
	// -------------- не удалять ------------
	return m_instanceCount;
	// -------------- не удалять ------------
}
