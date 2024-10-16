#pragma once
#include <string>

namespace Document
{

class IImage
{
public:
	virtual std::string GetPath() = 0;
	virtual int GetWidth() = 0;
	virtual int HetHeight() = 0;
	virtual void Resize(int width, int height) = 0;

	virtual ~IImage() = default;
};

} // namespace Document
