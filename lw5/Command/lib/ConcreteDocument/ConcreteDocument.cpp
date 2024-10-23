#include "ConcreteDocument.h"
#include "../HtmlWriter/HtmlWriter.h"
#include <iostream>

void ConcreteDocument::ConcreteDocument::InsertParagraph(const std::string& text, std::optional<size_t> pos)
{
	DocumentHistory::History* historyPtr = &m_history;
	auto fn = [historyPtr](std::string& text, const std::string& newText) {
		historyPtr->AddAndExecuteCommand(std::make_unique<DocHistoryCommands::ReplaceParagraphCommand>(text, newText));
	};

	m_history.AddAndExecuteCommand(std::make_unique<DocHistoryCommands::InsertParagraphCommand>(m_items, pos, text, fn));
}

void ConcreteDocument::ConcreteDocument::InsertImage(const std::string& path, int width, int height, std::optional<size_t> pos)
{
	DocumentHistory::History* historyPtr = &m_history;
	auto fn = [historyPtr](int& width, int& height, int newWidth, int newHeight) {
		historyPtr->AddAndExecuteCommand(std::make_unique<DocHistoryCommands::ResizeImageCommand>(width, height, newWidth, newHeight));
	};

	m_history.AddAndExecuteCommand(std::make_unique<DocHistoryCommands::InsertImageCommand>(m_items, pos, path, width, height, fn));
}

std::string ConcreteDocument::ConcreteDocument::GetTitle() const
{
	return m_title;
}

void ConcreteDocument::ConcreteDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<DocHistoryCommands::SetTitleCommand>(m_title, title));
}

size_t ConcreteDocument::ConcreteDocument::GetItemCount() const
{
	return m_items.size();
}

Document::DocumentItem ConcreteDocument::ConcreteDocument::GetItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::out_of_range("Index out of range collection");
	}

	return m_items[index];
}

Document::ConstDocumentItem ConcreteDocument::ConcreteDocument::GetItem(size_t index) const
{
	if (index >= m_items.size())
	{
		throw std::out_of_range("Index out of range collection");
	}

	return Document::ConstDocumentItem(m_items[index].GetParagraph(), m_items[index].GetImage());
}

void ConcreteDocument::ConcreteDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<DocHistoryCommands::DeleteItemCommand>(m_items, index));
}

bool ConcreteDocument::ConcreteDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void ConcreteDocument::ConcreteDocument::Undo()
{
	m_history.Undo();
}

bool ConcreteDocument::ConcreteDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void ConcreteDocument::ConcreteDocument::Redo()
{
	m_history.Redo();
}

void ConcreteDocument::ConcreteDocument::Save(const std::string& path) const
{
	std::vector<Document::ConstDocumentItem> items;

	for (const auto& item : m_items)
	{
		items.push_back(Document::ConstDocumentItem(item.GetParagraph(), item.GetImage()));
	}

	HtmlWriter::WriteHtmlToFile(m_title, items, path);
}
