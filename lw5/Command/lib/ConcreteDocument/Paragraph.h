#pragma once
#include "../Document/IParagraph.h"

namespace ConcreteDocument
{

class Paragraph : public Document::IParagraph
{
public:
	Paragraph(const std::string& text)
		: m_text(text){};
	std::string GetText() const override;
	void SetText(std::string text) override;

private:
	std::string m_text;
};

} // namespace ConcreteDocument
