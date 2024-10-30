#pragma once
#include <iomanip>
#include <iostream>

//���������� ��� ���������
namespace graphics_lib
{

// ����� ��� ���������
class ICanvas
{
public:
	// ��������� ����� � ������� 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	// ������ "����" � ����� x, y
	virtual void MoveTo(int x, int y) = 0;
	// ������ ����� � ������� �������, ���������� ���� � ����� x,y
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// ���������� ������ ��� ���������
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		uint8_t b = rgbColor;
		uint8_t g = rgbColor >> 8;
		uint8_t r = rgbColor >> 16;

		std::cout << "SetColor (#" << std::hex
				  << std::setw(2) << std::setfill('0') << static_cast<int>(r)
				  << std::setw(2) << std::setfill('0') << static_cast<int>(g)
				  << std::setw(2) << std::setfill('0') << static_cast<int>(b)
				  << std::dec << ")" << std::endl;
	}
	void MoveTo(int x, int y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(int x, int y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};

} // namespace graphics_lib
