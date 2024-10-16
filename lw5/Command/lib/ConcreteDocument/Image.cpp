#include "Image.h"

std::string ConcreteDocument::Image::GetPath() const
{
	return m_path;
}

int ConcreteDocument::Image::GetWidth() const
{
	return m_width;
}

int ConcreteDocument::Image::HetHeight() const
{
	return m_height;
}

void ConcreteDocument::Image::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}
