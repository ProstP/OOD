#include "Client.h"
#include <iostream>

void Client::Client::Run(std::istream& in, std::ostream& out)
{
	auto draft = m_designer->CreateDraft(in);
	out << "Created picture draft with " << draft.GetShapeCount() << " shapes." << std::endl
		<< std::endl;

	m_painter->DrawPicture(draft, *m_canvas);

	std::string exit;
	in >> exit;
}
