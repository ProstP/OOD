#pragma once
#include "../Document/IImage.h"
#include <functional>

namespace ConcreteDocument
{

class Image : public Document::IImage
{
public:
	Image(const std::string& path, int width, int height, std::function<void(int&, int&, int, int)> fn)
		: m_path(path)
		, m_width(width)
		, m_height(height)
		, m_resizeFunc(fn){};

	std::string GetPath() const override;
	int GetWidth() const override;
	int GetHeight() const override;
	void Resize(int width, int height) override;

	~Image();

private:
	std::string m_path;
	int m_width;
	int m_height;
	std::function<void(int&, int&, int, int)> m_resizeFunc;
};

} // namespace ConcreteDocument
