#include "Tile.h"

Tile::Tile(uint32_t color)
{
	m_pixels = std::vector<std::vector<uint32_t>>(SIZE, std::vector<uint32_t>(SIZE, color));

	// -------------- �� ������� ------------
	assert(m_instanceCount >= 0);
	++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
	// -------------- �� ������� ------------
}

Tile::Tile(const Tile& other)
{
	m_pixels = other.m_pixels;

	// -------------- �� ������� ------------
	assert(m_instanceCount >= 0);
	++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
	// -------------- �� ������� ------------
}

Tile::~Tile()
{
	// -------------- �� ������� ------------
	--m_instanceCount; // ��������� ������� ������.
	assert(m_instanceCount >= 0);
	// -------------- �� ������� ------------
}

void Tile::SetPixel(Point p, uint32_t color)
{
	if (p.x >= SIZE || p.y >= SIZE)
	{
		return;
	}

	m_pixels[p.x][p.y] = color;
}

uint32_t Tile::GetPixel(Point p) const
{
	if (p.x >= SIZE || p.y >= SIZE)
	{
		return ' ';
	}

	return m_pixels[p.x][p.y];
}

int Tile::GetInstanceCount() noexcept
{
	// -------------- �� ������� ------------
	return m_instanceCount;
	// -------------- �� ������� ------------
}
