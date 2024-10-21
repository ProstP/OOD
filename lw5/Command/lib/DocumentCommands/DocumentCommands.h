#pragma once
#include "../Command/ICommand.h"
#include "../Document/IDocument.h"
#include <iostream>
#include <optional>

namespace DocumentCommands
{

class InsertParagraphCommand : Command::ICommand
{
public:
	InsertParagraphCommand(Document::IDocument& document, const std::string& text, std::optional<size_t> pos = std::nullopt)
		: m_document(&document)
		, m_pos(pos)
		, m_text(text){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	std::optional<size_t> m_pos;
	std::string m_text;
};

class InsertImageCommand : Command::ICommand
{
public:
	InsertImageCommand(Document::IDocument& document, const std::string& path, int width, int height, std::optional<size_t> pos = std::nullopt)
		: m_document(&document)
		, m_pos(pos)
		, m_path(path)
		, m_width(width)
		, m_height(height){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	std::optional<size_t> m_pos;
	std::string m_path;
	int m_width;
	int m_height;
};

class SetTitleCommand : Command::ICommand
{
public:
	SetTitleCommand(Document::IDocument& document, const std::string& title)
		: m_document(&document)
		, m_title(title){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	std::string m_title;
};

class ListCommand : Command::ICommand
{
public:
	ListCommand(Document::IDocument& document, std::ostream& out)
		: m_document(&document)
		, m_out(&out){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	std::ostream* m_out;
};

class ReplaceParagraphCommand : Command::ICommand
{
public:
	ReplaceParagraphCommand(Document::IDocument& document, size_t pos, const std::string& text)
		: m_document(&document)
		, m_pos(pos)
		, m_text(text){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	size_t m_pos;
	std::string m_text;
};

class ResizeImageCommand : Command::ICommand
{
public:
	ResizeImageCommand(Document::IDocument& document, size_t pos, int width, int height)
		: m_document(&document)
		, m_pos(pos)
		, m_width(width)
		, m_height(height){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	size_t m_pos;
	int m_width;
	int m_height;
};

class DeleteItemCommand : Command::ICommand
{
public:
	DeleteItemCommand(Document::IDocument& document, size_t index)
		: m_document(&document)
		, m_index(index){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	size_t m_index;
};

class UndoCommand : Command::ICommand
{
public:
	UndoCommand(Document::IDocument& document)
		: m_document(&document){};
	void Execute() override;

private:
	Document::IDocument* m_document;
};

class RedoCommand : Command::ICommand
{
public:
	RedoCommand(Document::IDocument& document)
		: m_document(&document){};
	void Execute() override;

private:
	Document::IDocument* m_document;
};

class SaveCommand : Command::ICommand
{
public:
	SaveCommand(Document::IDocument& document, const std::string& path)
		: m_document(&document)
		, m_path(path){};
	void Execute() override;

private:
	Document::IDocument* m_document;
	std::string m_path;
};

} // namespace DocumentCommands
