#pragma once
#include "../Document/IDocument.h"
#include <string>
#include <vector>

class HtmlWriter
{
public:
	static void WriteHtmlToFile(Document::IDocument& document, const std::string& outFileName);

private:
	static std::string HtmlEndodeStr(const std::string str);
};
