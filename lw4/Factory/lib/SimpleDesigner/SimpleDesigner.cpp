#include "SimpleDesigner.h"
#include <iostream>
#include <regex>
#include <string>

Shapes::PictureDraft SimpleDesigner::SimpleDesigner::CreateDraft(std::istream& in)
{
	const std::regex pattern("^(\\w+)\\s+(.+)$");
	std::string line;

	Shapes::PictureDraft draft;

	while (std::getline(in, line))
	{
		try
		{
			std::smatch m;
			if (!std::regex_match(line, m, pattern))
			{
				throw std::invalid_argument("Invalid command to create shape");
			}

			draft.AddShape(m_factory->CreateShape(m[1].str(), m[2].str()));
		}
		catch (...)
		{
			break;
		}
	}

	return draft;
}
