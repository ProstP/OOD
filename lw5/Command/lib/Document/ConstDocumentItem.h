#pragma once
#include "IImage.h"
#include "IParagraph.h"
#include <memory>

namespace Document
{

class ConstDocumentItem
{
public:
	ConstDocumentItem(const std::shared_ptr<const IParagraph> paragraph, const std::shared_ptr<IImage> image)
		: m_paragraph(paragraph)
		, m_image(image){};
	[[nodiscard]] std::shared_ptr<const IParagraph> GetParagraph() const;
	[[nodiscard]] std::shared_ptr<const IImage> GetImage() const;

private:
	std::shared_ptr<const IParagraph> m_paragraph;
	std::shared_ptr<const IImage> m_image;
};

} // namespace Document
