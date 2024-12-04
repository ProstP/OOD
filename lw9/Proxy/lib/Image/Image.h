#pragma once
#include "../CoW/CoW.h"
#include "../Geom/Geom.h"
#include "Tile.h"
#include <iosfwd>
#include <string>
#include <vector>

class Image
{
public:
	/**
     * ������������ ����������� ��������� �������. ���� ������� �� �������� ��������������,
     * ����������� ���������� std::out_of_range.
     */
	Image(Size size, uint32_t color = ' ');

	// ���������� ������ ����������� � ��������.
	Size GetSize() const noexcept;

	/**
     * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
     * �����������, ���������� �������.
     */
	uint32_t GetPixel(Point p) const noexcept;

	/**
     * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
     * �������� ������������.
     */
	void SetPixel(Point p, uint32_t color);

private:
	std::vector<std::vector<CoW<Tile>>> m_tiles;
	Size m_size;
};

/**
 * ������� � ����� out ����������� � ���� ��������.
 */
void Print(const Image& img, std::ostream& out);

/**
 * ��������� ����������� �� pixels. ����� ����������� ����������� ��������� \n.
 * ������� �������� ������������ �� ���������� ��������� ������ � ����� ������� �����.
 */
Image LoadImage(const std::string& pixels);

void SaveImage(const Image& image, const std::string& fileName);
