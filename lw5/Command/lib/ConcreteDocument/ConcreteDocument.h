#pragma once
#include "../Document/IDocument.h"
#include <vector>
#include "../History/History.h"

namespace ConcreteDocument
{

class ConcreteDocument : public Document::IDocument
{
public:
	void InsertParagraph(const std::string& text, std::optional<size_t> pos = std::nullopt) override;
	void InsertImage(const std::string& path, int width, int height, std::optional<size_t> pos = std::nullopt) override;
	std::string GetTitle() const override;
	void SetTitle(const std::string& title) override;
	size_t GetItemCount() const override;
	Document::DocumentItem GetItem(size_t index) override;
	Document::ConstDocumentItem GetItem(size_t index) const override;
	void DeleteItem(size_t index) override;
	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;
	void Save(const std::string& path) const override;

	~ConcreteDocument() override = default;
private:
	std::string m_title;
	std::vector<Document::DocumentItem> m_items;
	DocumentHistory::History m_history;
};

} // namespace ConcreteDocument
