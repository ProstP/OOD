#pragma once
#include "../Document/IParagraph.h"
#include <functional>

namespace ConcreteDocument
{

class Paragraph : public Document::IParagraph
{
public:
	Paragraph(const std::string& text, std::function<void(std::string& text, std::string newText)> fn)
		: m_text(text)
		, m_SetTextFn(fn){};
	std::string GetText() const override;
	void SetText(std::string text) override;

private:
	std::function<void(std::string& text, const std::string& newText)> m_SetTextFn;
	std::string m_text;
};

} // namespace ConcreteDocument
