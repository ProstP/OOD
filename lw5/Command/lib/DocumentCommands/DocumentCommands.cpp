#include "DocumentCommands.h"

void DocumentCommands::InsertParagraphCommand::Execute()
{
	m_document->InsertParagraph(m_text, m_pos);
}

void DocumentCommands::InsertImageCommand::Execute()
{
	m_document->InsertImage(m_path, m_width, m_height, m_pos);
}

void DocumentCommands::SetTitleCommand::Execute()
{
	m_document->SetTitle(m_title);
}

void DocumentCommands::ListCommand::Execute()
{
	*m_out << "<---------->" << std::endl;
	*m_out << m_document->GetTitle();
	for (size_t i = 0; i < m_document->GetItemCount(); i++)
	{
		*m_out << i << ":";

		auto item = m_document->GetItem(i);
		if (item.GetParagraph() != nullptr)
		{
			*m_out << item.GetParagraph()->GetText();
		}
		else if (item.GetImage() != nullptr)
		{
			*m_out << item.GetImage()->GetWidth() << " " << item.GetImage()->HetHeight() << " " << item.GetImage()->GetPath();
		}

		*m_out << std::endl;
	}

	*m_out << "<---------->" << std::endl;
}

void DocumentCommands::ReplaceParagraphCommand::Execute()
{
	auto item = m_document->GetItem(m_pos);

	if (item.GetParagraph() == nullptr)
	{
		throw std::invalid_argument("Item not paragraph");
	}

	item.GetParagraph()->SetText(m_text);
}

void DocumentCommands::ResizeImageCommand::Execute()
{
	auto item = m_document->GetItem(m_pos);

	if (item.GetImage() == nullptr)
	{
		throw std::invalid_argument("Item not image");
	}

	item.GetImage()->Resize(m_width, m_height);
}

void DocumentCommands::DeleteItemCommand::Execute()
{
	m_document->DeleteItem(m_index);
}

void DocumentCommands::UndoCommand::Execute()
{
	if (!m_document->CanUndo())
	{
		throw std::invalid_argument("Document can't do undo");
	}

	m_document->Undo();
}

void DocumentCommands::RedoCommand::Execute()
{
	if (!m_document->CanRedo())
	{
		throw std::invalid_argument("Document can't do undo");
	}

	m_document->Redo();
}

void DocumentCommands::SaveCommand::Execute()
{
	m_document->Save(m_path);
}
