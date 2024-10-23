#pragma once
#include "../Document/DocumentItem.h"
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace DocHistoryCommands
{

class AbstractDocumentCommand
{
public:
	void Execute();
	void Unexecute();
	bool IsExecuted() const;

	virtual ~AbstractDocumentCommand() = default;

protected:
	virtual void ExecuteImp() = 0;
	virtual void UnexecuteImp() = 0;

private:
	bool m_isExecuted = true;
};

class InsertParagraphCommand : public AbstractDocumentCommand
{
public:
	InsertParagraphCommand(std::vector<Document::DocumentItem>& items, std::optional<size_t> pos, const std::string& text, std::function<void(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&&)> fn);

	~InsertParagraphCommand() override = default;

protected:
	void ExecuteImp() override;
	void UnexecuteImp() override;

private:
	std::vector<Document::DocumentItem>* m_items;
	std::optional<size_t> m_pos;
	Document::DocumentItem m_item;
};

class InsertImageCommand : public AbstractDocumentCommand
{
public:
	InsertImageCommand(std::vector<Document::DocumentItem>& items, std::optional<size_t> pos, const std::string& path, int width, int height, std::function<void(std::unique_ptr<DocHistoryCommands::AbstractDocumentCommand>&&)> fn);

	~InsertImageCommand() override = default;

protected:
	void ExecuteImp() override;
	void UnexecuteImp() override;

private:
	std::vector<Document::DocumentItem>* m_items;
	std::optional<size_t> m_pos;
	Document::DocumentItem m_item;
};

class SetTitleCommand : public AbstractDocumentCommand
{
public:
	SetTitleCommand(std::string& title, const std::string& text)
		: m_titlePtr(&title)
		, m_text(text)
		, m_oldText(title){};

	~SetTitleCommand() override = default;

protected:
	void ExecuteImp() override;
	void UnexecuteImp() override;

private:
	std::string* m_titlePtr;
	std::string m_text;
	std::string m_oldText;
};

class ReplaceParagraphCommand : public AbstractDocumentCommand
{
public:
	ReplaceParagraphCommand(std::string& item, const std::string& text)
		: m_item(&item)
		, m_text(text)
		, m_oldText(item){};

	~ReplaceParagraphCommand() override = default;

protected:
	void ExecuteImp() override;
	void UnexecuteImp() override;

private:
	std::string* m_item;
	std::string m_text;
	std::string m_oldText;
};

class ResizeImageCommand : public AbstractDocumentCommand
{
public:
	ResizeImageCommand(int& width, int& height, int newWidth, int newHeight)
		: m_w(&width)
		, m_h(&height)
		, m_newW(newWidth)
		, m_newH(newHeight)
		, m_oldW(width)
		, m_oldH(height){};

	~ResizeImageCommand() override = default;

protected:
	void ExecuteImp() override;
	void UnexecuteImp() override;

private:
	int* m_w;
	int* m_h;
	int m_newW;
	int m_newH;
	int m_oldW;
	int m_oldH;
};

class DeleteItemCommand : public AbstractDocumentCommand
{
public:
	DeleteItemCommand(std::vector<Document::DocumentItem>& items, size_t pos);

	~DeleteItemCommand() override = default;

protected:
	void ExecuteImp() override;
	void UnexecuteImp() override;

private:
	std::vector<Document::DocumentItem>* m_items;
	size_t m_pos;
	Document::DocumentItem m_itemCopy;
};

} // namespace DocHistoryCommands
