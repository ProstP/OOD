#include "ConstDocumentItem.h"

std::shared_ptr<const Document::IParagraph> Document::ConstDocumentItem::GetParagraph() const
{
    return m_paragraph;
}

std::shared_ptr<const Document::IImage> Document::ConstDocumentItem::GetImage() const
{
    return m_image;
}
