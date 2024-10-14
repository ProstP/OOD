#include "SimpleDesigner.h"
#include <iostream>
#include <string>

Shapes::PictureDraft SimpleDesigner::SimpleDesigner::CreateDraft(std::istream& in)
{
	std::string line;

	Shapes::PictureDraft draft;

	while (std::getline(in, line))
	{
		try
		{
			draft.AddShape(std::move(m_factory->CreateShape(line)));
		}
		catch (...)
		{
			break;
		}
	}

	return draft;
}
