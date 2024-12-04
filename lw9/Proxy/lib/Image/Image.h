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
	Image(Size size, char color = ' ');

	// ���������� ������ ����������� � ��������.
	Size GetSize() const noexcept;

	/**
     * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
     * �����������, ���������� �������.
     */
	char GetPixel(Point p) const noexcept;

	/**
     * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
     * �������� ������������.
     */
	void SetPixel(Point p, char color);

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
