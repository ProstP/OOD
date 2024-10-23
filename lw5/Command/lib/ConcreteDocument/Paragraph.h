#pragma once
#include "../DocHistoryCommands/DocHistoryCommands.h"
#include "../Document/IParagraph.h"
#include <functional>

namespace ConcreteDocument
{

class Paragraph : public Document::IParagraph
{
public:
	Paragraph(const std::string& text, std::function<void(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&&)> fn)
		: m_text(text)
		, m_SetTextFn(fn){};
	std::string GetText() const override;
	void SetText(std::string text) override;

private:
	std::function<void(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&&)> m_SetTextFn;
	std::string m_text;
};

} // namespace ConcreteDocument
