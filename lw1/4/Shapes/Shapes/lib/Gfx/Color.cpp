#include "Color.h"

Color::Color(const std::string& colorInHex)
{
	m_r = FromHexToDec(colorInHex.substr(0, 2));
	m_g = FromHexToDec(colorInHex.substr(2, 2));
	m_b = FromHexToDec(colorInHex.substr(4, 2));
}

unsigned char Color::GetR() const
{
	return m_r;
}

unsigned char Color::GetG() const
{
	return m_g;
}

unsigned char Color::GetB() const
{
	return m_b;
}

std::string Color::GetInHex() const
{
	return std::string();
}

unsigned char Color::FromHexToDec(const std::string& hex)
{
	unsigned char dec = 0;

	for (size_t i = 0; i < hex.length(); i++)
	{
		const int radix = 16;

		char ch = hex[i];
		unsigned char summand;

		if ('0' <= ch && ch <= '9')
		{
			summand = ch - '0';
		}
		else if ('a' <= ch && ch <= 'f')
		{
			summand = 10 + ch - 'a';
		}
		else
		{
			throw std::invalid_argument("Unknown symbol in hex form of color");
		}

		dec = dec * radix + summand;
	}

	return dec;
}
