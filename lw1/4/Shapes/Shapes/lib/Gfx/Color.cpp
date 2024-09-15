#include "Color.h"

Color::Color(const std::string& colorInHex)
{
	m_r = 0;
	m_g = 0;
	m_b = 0;
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
