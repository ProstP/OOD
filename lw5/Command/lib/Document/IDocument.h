#pragma once
#include "ConstDocumentItem.h"
#include "DocumentItem.h"
#include <optional>
#include <string>

namespace Document
{

class IDocument
{
public:
	virtual void InsertParagraph(const std::string& text, std::optional<size_t> pos = std::nullopt) = 0;
	virtual void InsertImage(const std::string& path, int width, int height, std::optional<size_t> pos = std::nullopt) = 0;
	virtual std::string GetTitle() const = 0;
	virtual void SetTitle(const std::string& title) = 0;
	virtual size_t GetItemCount() const = 0;
	virtual DocumentItem GetItem(size_t index) = 0;
	virtual ConstDocumentItem GetItem(size_t index) const = 0;
	virtual void DeleteItem(size_t index) = 0;
	virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;
	virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;
	virtual void Save(const std::string& path) const = 0;

	virtual ~IDocument() = default;
};

} // namespace Document
