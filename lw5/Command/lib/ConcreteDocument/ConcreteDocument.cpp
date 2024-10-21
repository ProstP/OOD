#include "ConcreteDocument.h"

void ConcreteDocument::ConcreteDocument::InsertParagraph(const std::string& text, std::optional<size_t> pos = std::nullopt)
{

}

void ConcreteDocument::ConcreteDocument::InsertImage(const std::string& path, int width, int height, std::optional<size_t> pos = std::nullopt)
{
}

std::string ConcreteDocument::ConcreteDocument::GetTitle() const
{
    return std::string();
}

void ConcreteDocument::ConcreteDocument::SetTitle(const std::string& title)
{
}

size_t ConcreteDocument::ConcreteDocument::GetItemCount() const
{
    return size_t();
}

Document::DocumentItem ConcreteDocument::ConcreteDocument::GetItem(size_t index)
{
}

Document::ConstDocumentItem ConcreteDocument::ConcreteDocument::GetItem(size_t index) const
{
}

void ConcreteDocument::ConcreteDocument::DeleteItem(size_t index)
{
}

bool ConcreteDocument::ConcreteDocument::CanUndo() const
{
    return false;
}

void ConcreteDocument::ConcreteDocument::Undo()
{
}

bool ConcreteDocument::ConcreteDocument::CanRedo() const
{
    return false;
}

void ConcreteDocument::ConcreteDocument::Redo()
{
}

void ConcreteDocument::ConcreteDocument::Save(const std::string& path) const
{
}
