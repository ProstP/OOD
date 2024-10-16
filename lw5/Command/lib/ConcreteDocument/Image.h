#pragma once
#include "../Document/IImage.h"

namespace ConcreteDocument
{

class Image : public Document::IImage
{
public:
	Image(const std::string& path, int width, int height)
		: m_path(path)
		, m_width(width)
		, m_height(height){};

	std::string GetPath() const override;
	int GetWidth() const override;
	int HetHeight() const override;
	void Resize(int width, int height) override;

private:
	std::string m_path;
	int m_width;
	int m_height;
};

} // namespace ConcreteDocument
