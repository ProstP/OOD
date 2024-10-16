#pragma once
#include "ConstDocumentItem.h"

namespace Document
{

class DocumentItem
{
public:
	DocumentItem(const std::shared_ptr<IParagraph> paragraph, const std::shared_ptr<IImage> image)
		: m_paragraph(paragraph)
		, m_image(image){};
	[[nodiscard]] std::shared_ptr<IParagraph> GetParagraph() const;
	[[nodiscard]] std::shared_ptr<IImage> GetImage() const;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};

} // namespace Document
