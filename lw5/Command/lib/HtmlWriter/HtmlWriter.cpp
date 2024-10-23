#include "HtmlWriter.h"
#include "../FileUtils/FileUtils.h"
#include <fstream>

void HtmlWriter::WriteHtmlToFile(const std::string& title, std::vector<Document::ConstDocumentItem> items, const std::string& outFilePath)
{
	std::ofstream out(outFilePath);
	if (!out.is_open())
	{
		throw std::invalid_argument("Failed in open file");
	}

	out << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
	out << "<title>" << HtmlEndodeStr(title) << "</title>\n";
	out << "</head>\n<body>\n";

	for (int i = 0; i < items.size(); i++)
	{
		auto item = items[i];

		if (item.GetParagraph() != nullptr)
		{
			out << "<p>" << HtmlEndodeStr(item.GetParagraph()->GetText()) << "</p>\n";
		}
		else if (item.GetImage() != nullptr)
		{
			std::string path = HtmlEndodeStr(item.GetImage()->GetPath());
			std::string newPath = FileUtils::GetParantPath(outFilePath) + "/" + path;
			FileUtils::CopyFiles(path, newPath);

			out << "<img src=\"" << path
				<< "\" width=" << item.GetImage()->GetWidth()
				<< " height=" << item.GetImage()->GetHeight()
				<< " />\n";
		}
	}

	out << "</body>\n</html>";
}

std::string HtmlWriter::HtmlEndodeStr(const std::string str)
{
	std::string encoded;

	for (const char ch : str)
	{
		switch (ch)
		{
		case '"':
			encoded += "&quot;";
			break;
		case '\'':
			encoded += "&apos;";
			break;
		case '<':
			encoded += "&lt;";
			break;
		case '>':
			encoded += "&gt;";
			break;
		case '&':
			encoded += "&amp;";
			break;
		default:
			encoded += ch;
			break;
		}
	}

	return encoded;
}
