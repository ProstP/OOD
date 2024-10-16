#pragma once
#include <string>

namespace Document
{

class IParagraph
{
public:
	virtual std::string GetText() const = 0;
	virtual void SetText(std::string text) = 0;

	virtual ~IParagraph() = default;
};

} // namespace Document
