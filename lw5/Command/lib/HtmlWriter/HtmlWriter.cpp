#include "HtmlWriter.h"
#include <fstream>

void HtmlWriter::WriteHtmlToFile(Document::IDocument& document, const std::string& outFileName)
{
	std::ofstream out(outFileName);
	if (!out.is_open())
	{
		throw std::invalid_argument("Failed in open file");
	}

	out << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
	out << "<title>" << HtmlEndodeStr(document.GetTitle()) << "</title>\n";
	out << "</head>\n<body>\n";

	for (int i = 0; i < document.GetItemCount(); i++)
	{
		auto item = document.GetItem(i);

		if (item.GetParagraph() != nullptr)
		{
			out << "<p>" << HtmlEndodeStr(item.GetParagraph()->GetText()) << "</p>\n";
		}
		else if (item.GetImage() != nullptr)
		{
			out << "<img src=\"" << HtmlEndodeStr(item.GetImage()->GetPath())
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
