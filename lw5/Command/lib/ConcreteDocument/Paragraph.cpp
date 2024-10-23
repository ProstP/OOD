#include "Paragraph.h"

std::string ConcreteDocument::Paragraph::GetText() const
{
	return m_text;
}

void ConcreteDocument::Paragraph::SetText(std::string text)
{
	m_SetTextFn(m_text, text);
}
