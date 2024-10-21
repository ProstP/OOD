#pragma once
#include "../DocHistoryCommands/DocHistoryCommands.h"
#include <iostream>
#include <vector>

namespace DocumentHistory
{

class History
{
public:
	void AddAndExecuteCommand(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&& command);
	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();

private:
	std::vector<std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>> m_commands;
	size_t m_current;
};

} // namespace DocumentHistory
