#include "DocumentItem.h"

std::shared_ptr<Document::IParagraph> Document::DocumentItem::GetParagraph() const
{
    return m_paragraph;
}

std::shared_ptr<Document::IImage> Document::DocumentItem::GetImage() const
{
    return m_image;
}
