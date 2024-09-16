#pragma once
#include <iostream>

class Color
{
public:
	Color(const std::string& colorInHex);
	unsigned char GetR() const;
	unsigned char GetG() const;
	unsigned char GetB() const;
	std::string GetInHex() const;

private:
	unsigned char m_r;
	unsigned char m_g;
	unsigned char m_b;

	static unsigned char FromHexToDec(const std::string& hex);
	static std::string FromDecToHex(unsigned char dec);
};
