#include "Image.h"
#include <filesystem>
#include <iostream>

std::string ConcreteDocument::Image::GetPath() const
{
	return m_path;
}

int ConcreteDocument::Image::GetWidth() const
{
	return m_width;
}

int ConcreteDocument::Image::GetHeight() const
{
	return m_height;
}

void ConcreteDocument::Image::Resize(int width, int height)
{
	m_resizeFunc(m_width, m_height, width, height);
}

ConcreteDocument::Image::~Image()
{
	std::filesystem::path path(m_path);
	std::filesystem::remove(path);
}
