#pragma once
#include "../Command/IUnexecutableCommand.h"
#include "../Document/IDocument.h"

namespace DocumentCommands
{

class AbstractDocumentCommand : public Command::IUnexecutableCommand
{
public:
	AbstractDocumentCommand(Document::IDocument& document)
		: m_document(&document){};

protected:
	Document::IDocument* m_document;
};

class InsertParagraphCommand : AbstractDocumentCommand
{
};

} // namespace DocumentCommands
