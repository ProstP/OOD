#pragma once
#include "../Document/ConstDocumentItem.h"
#include <string>
#include <vector>

class HtmlWriter
{
public:
	static void WriteHtmlToFile(const std::string& title, std::vector<Document::ConstDocumentItem> items, const std::string& outFileName);

private:
	static std::string HtmlEndodeStr(const std::string str);
};
