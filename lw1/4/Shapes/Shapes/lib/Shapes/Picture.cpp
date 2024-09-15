#include "Picture.h"

void Picture::AddShape(const std::string& id, const std::string& color, const std::string& type, const std::string& params)
{
}

void Picture::MoveShape(const std::string&, double dx, double dy)
{
}

void Picture::MovePicture(double dx, double dy)
{
}

void Picture::DeleteShape(const std::string& id)
{
}

void Picture::List(std::ostream& out) const
{
}

void Picture::ChangeColor(const std::string& id, const std::string& color)
{
}

void Picture::ChangeShape(const std::string& id, const std::string& type, const std::string& params)
{
}

void Picture::DrawShape(const std::string& id)
{
}

void Picture::DrawPicture()
{
}

void Picture::SetCanvas(const ICanvas& canvas)
{
	*m_canvas = canvas;
}

Picture::~Picture()
{
	delete m_canvas;
}
