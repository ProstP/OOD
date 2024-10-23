#include "History.h"

void DocumentHistory::History::AddAndExecuteCommand(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&& command)
{
	if (m_commands.empty())
	{
		m_commands.push_back(std::move(command));
	}
	else
	{
		if (!m_commands[m_commands.size() - 1]->IsExecuted())
		{
			if (!m_commands[0]->IsExecuted())
			{
				m_commands.clear();
			}
			else
			{
				m_commands.resize(m_current + 1);
			}
		}

		m_commands.push_back(std::move(command));

		if (m_commands.size() >= 11)
		{
			m_commands.erase(m_commands.begin());
		}
	}

	m_current = m_commands.size() - 1;
	m_commands[m_current]->Execute();
}

bool DocumentHistory::History::CanUndo() const
{
	if (m_commands.size() == 0 || !m_commands[0]->IsExecuted())
	{
		return false;
	}

	return true;
}

void DocumentHistory::History::Undo()
{
	if (!CanUndo())
	{
		throw std::invalid_argument("Can't undo");
	}

	if (!m_commands[m_current]->IsExecuted())
	{
		throw std::invalid_argument("Action not executed to undo");
	}

	m_commands[m_current]->Unexecute();
	m_current = m_current == 0 ? 0 : m_current - 1;
}

bool DocumentHistory::History::CanRedo() const
{
	if (m_commands.size() == 0 || (m_current == m_commands.size() - 1 && m_commands[0]->IsExecuted()))
	{
		return false;
	}

	return true;
}

void DocumentHistory::History::Redo()
{
	if (!CanRedo())
	{
		throw std::invalid_argument("Can't redo");
	}

	if (m_commands[m_current + 1]->IsExecuted())
	{
		throw std::invalid_argument("Action already execute to redo");
	}
	m_current = m_commands[0]->IsExecuted() ? m_current + 1 : 0;
	m_commands[m_current]->Execute();
}
