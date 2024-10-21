#include "History.h"

void DocumentHistory::History::AddAndExecuteCommand(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&& command)
{
	if (m_commands[m_commands.size() - 1]->IsExecuted())
	{
		m_commands.push_back(std::move(command));

		if (m_commands.size() >= 11)
		{
			//m_commands.erase(;
		}
	}
	else
	{
	}

	m_current = m_commands.size() - 1;
	m_commands[m_current]->Execute();
}

bool DocumentHistory::History::CanUndo() const
{
	if (m_current == 0)
	{
		return false;
	}

	return true;
}

void DocumentHistory::History::Undo()
{
	if (CanUndo())
	{
		throw std::invalid_argument("Can't undo");
	}

	if (!m_commands[m_current]->IsExecuted())
	{
		throw std::invalid_argument("Action not executed to undo");
	}
	m_commands[m_current]->Unexecute();
	m_current--;
}

bool DocumentHistory::History::CanRedo() const
{
	if (m_current == m_commands.size() - 1)
	{
		return false;
	}

	return true;
}

void DocumentHistory::History::Redo()
{
	if (CanRedo())
	{
		throw std::invalid_argument("Can't redo");
	}

	if (m_commands[m_current]->IsExecuted())
	{
		throw std::invalid_argument("Action already execute to redo");
	}
	m_commands[m_current]->Execute();
	m_current++;
}
