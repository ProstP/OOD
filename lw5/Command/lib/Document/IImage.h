#pragma once
#include <string>

namespace Document
{

class IImage
{
public:
	virtual std::string GetPath() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void Resize(int width, int height) = 0;

	virtual ~IImage() = default;
};

} // namespace Document
