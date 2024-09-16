#include "Color.h"
#include <cmath>

Color::Color(const std::string& colorInHex)
{
	if (colorInHex.length() != 6)
	{
		throw std::invalid_argument("Hex length must be equal 6");
	}

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
	std::string hex;

	hex += FromDecToHex(m_r);
	hex += FromDecToHex(m_g);
	hex += FromDecToHex(m_b);

	return hex;
}

unsigned char Color::FromHexToDec(const std::string& hex)
{
	const int radix = 16;
	unsigned char dec = 0;

	for (size_t i = 0; i < hex.length(); i++)
	{
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

std::string Color::FromDecToHex(unsigned char dec)
{
	std::string hex;
	const int radix = 16;

	do
	{
		int remainder = abs(dec % radix);
		dec = dec / radix;

		char ch;

		if (0 <= remainder && remainder <= 9)
		{
			ch = '0' + remainder;
		}
		else
		{
			ch = 'a' + remainder - 10;
		}

		hex += ch;
	} while (dec != 0);

	std::reverse(hex.begin(), hex.end());
	return hex;
}
