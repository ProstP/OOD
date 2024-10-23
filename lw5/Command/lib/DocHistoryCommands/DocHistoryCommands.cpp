#include "DocHistoryCommands.h"
#include "../ConcreteDocument/Image.h"
#include "../ConcreteDocument/Paragraph.h"
#include <iostream>

void DocHistoryCommands::AbstractDocumentCommand::Execute()
{
	m_isExecuted = true;

	ExecuteImp();
}

void DocHistoryCommands::AbstractDocumentCommand::Unexecute()
{
	m_isExecuted = false;

	UnexecuteImp();
}

bool DocHistoryCommands::AbstractDocumentCommand::IsExecuted() const
{
	return m_isExecuted;
}

DocHistoryCommands::InsertParagraphCommand::InsertParagraphCommand(std::vector<Document::DocumentItem>& items, std::optional<size_t> pos, const std::string& text, std::function<void(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&&)> fn)
	: m_items(&items)
{
	m_pos = pos;
	if (pos != std::nullopt)
	{
		if (pos.value() >= m_items->size())
		{
			throw std::out_of_range("Out of range in inserting paragraph");
		}
	}

	m_item = Document::DocumentItem(std::make_shared<ConcreteDocument::Paragraph>(text, fn), nullptr);
}

void DocHistoryCommands::InsertParagraphCommand::ExecuteImp()
{
	if (m_pos == std::nullopt)
	{
		m_items->push_back(m_item);
	}
	else
	{
		auto pos = m_pos.value();

		m_items->insert(m_items->begin() + pos, m_item);
	}
}

void DocHistoryCommands::InsertParagraphCommand::UnexecuteImp()
{
	if (m_pos == std::nullopt)
	{
		m_items->pop_back();
	}
	else
	{
		m_items->erase(m_items->begin() + m_pos.value());
	}
}

DocHistoryCommands::InsertImageCommand::InsertImageCommand(std::vector<Document::DocumentItem>& items, std::optional<size_t> pos, const std::string& path, int width, int height, std::function<void(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&&)> fn)
	: m_items(&items)
{
	m_pos = pos;
	if (pos != std::nullopt)
	{
		if (pos.value() >= m_items->size())
		{
			throw std::out_of_range("Out of range in inserting inage");
		}
	}

	m_item = Document::DocumentItem(nullptr, std::make_shared<ConcreteDocument::Image>(path, width, height, fn));
}

void DocHistoryCommands::InsertImageCommand::ExecuteImp()
{
	if (m_pos == std::nullopt)
	{
		m_items->push_back(m_item);
	}
	else
	{
		m_items->insert(m_items->begin() + m_pos.value(), m_item);
	}
}

void DocHistoryCommands::InsertImageCommand::UnexecuteImp()
{
	if (m_pos == std::nullopt)
	{
		m_items->pop_back();
	}
	else
	{
		m_items->erase(m_items->begin() + m_pos.value());
	}
}

void DocHistoryCommands::SetTitleCommand::ExecuteImp()
{
	*m_titlePtr = m_text;
}

void DocHistoryCommands::SetTitleCommand::UnexecuteImp()
{
	*m_titlePtr = m_oldText;
}

void DocHistoryCommands::ReplaceParagraphCommand::ExecuteImp()
{
	*m_item = m_text;
}

void DocHistoryCommands::ReplaceParagraphCommand::UnexecuteImp()
{
	*m_item = m_oldText;
}

void DocHistoryCommands::ResizeImageCommand::ExecuteImp()
{
	*m_w = m_newW;
	*m_h = m_newH;
}

void DocHistoryCommands::ResizeImageCommand::UnexecuteImp()
{
	*m_w = m_oldW;
	*m_h = m_oldH;
}

DocHistoryCommands::DeleteItemCommand::DeleteItemCommand(std::vector<Document::DocumentItem>& items, size_t pos)
{
	m_items = &items;

	m_pos = pos;
	if (pos >= m_items->size())
	{
		throw std::out_of_range("Out of range in deleting item");
	}

	m_itemCopy = Document::DocumentItem(items[m_pos].GetParagraph(), items[m_pos].GetImage());
}

void DocHistoryCommands::DeleteItemCommand::ExecuteImp()
{
	if (m_pos >= m_items->size())
	{
		throw std::out_of_range("Index to delete out of range collection");
	}

	m_items->erase(m_items->begin() + m_pos);
}

void DocHistoryCommands::DeleteItemCommand::UnexecuteImp()
{
	m_items->insert(m_items->begin() + m_pos, m_itemCopy);
}
