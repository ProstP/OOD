#include "Picture.h"
#include "../Figure/Imp/Circle/Circle.h"
#include "../Figure/Imp/Line/Line.h"
#include "../Figure/Imp/Rectangle/Rectangle.h"
#include "../Figure/Imp/Text/TextFigure.h"
#include "../Figure/Imp/Traingle/Triangle.h"
#include <memory>
#include <string>

void Picture::AddShape(const std::string& id, const std::string& color, const std::string& type, const std::string& params)
{
	IsIdUsed(id);

	m_shapes.push_back(std::make_shared<Shape>(CreateShape(id, type, color, params)));
}

void Picture::MoveShape(const std::string& id, double dx, double dy)
{
	int index = FindIndexById(id);

	if (index == -1)
	{
		throw std::invalid_argument("Uknwown id");
	}

	m_shapes[index]->MoveShape(dx, dy);
}

void Picture::MovePicture(double dx, double dy)
{
	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i]->MoveShape(dx, dy);
	}
}

void Picture::DeleteShape(const std::string& id)
{
	int index = FindIndexById(id);

	if (index == -1)
	{
		throw std::invalid_argument("Uknwown id");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void Picture::List(std::ostream& out) const
{
	for (int i = 0; i < m_shapes.size(); i++)
	{
		out << m_shapes[i]->ToString() << std::endl;
	}
}

void Picture::ChangeColor(const std::string& id, const std::string& color)
{
	int index = FindIndexById(id);

	if (index == -1)
	{
		throw std::invalid_argument("Uknwown id");
	}

	m_shapes[index]->SetColor(Color(color));
}

void Picture::ChangeShape(const std::string& id, const std::string& type, const std::string& params)
{
	int index = FindIndexById(id);

	if (index == -1)
	{
		throw std::invalid_argument("Uknwown id");
	}

	if (type == "circle")
	{
		return m_shapes[index]->SetFigure(std::make_unique<Circle>(params));
	}
	else if (type == "rectangle")
	{
		return m_shapes[index]->SetFigure(std::make_unique<Rectangle>(params));
	}
	else if (type == "triangle")
	{
		return m_shapes[index]->SetFigure(std::make_unique<Triangle>(params));
	}
	else if (type == "line")
	{
		return m_shapes[index]->SetFigure(std::make_unique<Line>(params));
	}
	else if (type == "text")
	{
		return m_shapes[index]->SetFigure(std::make_unique<TextFigure>(params));
	}
	else
	{
		throw std::invalid_argument("Unknown type");
	}
}

void Picture::DrawShape(const std::string& id)
{
	int index = FindIndexById(id);

	if (index == -1)
	{
		throw std::invalid_argument("Uknwown id");
	}

	m_shapes[index]->Draw(*m_canvas);
}

void Picture::DrawPicture()
{
	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i]->Draw(*m_canvas);
	}
}

void Picture::SetCanvas(ICanvas* canvas)
{
	m_canvas = canvas;
	canvas = nullptr;
}

Picture::~Picture()
{
	m_canvas = nullptr;
}

void Picture::IsIdUsed(const std::string& id)
{
	for (int i = 0; i < m_shapes.size(); i++)
	{
		if (m_shapes[i]->GetId() == id)
		{
			throw std::invalid_argument("Id alredy used");
		}
	}
}

Shape Picture::CreateShape(const std::string& id, const std::string& type, const std::string& color, const std::string& params)
{
	if (type == "circle")
	{
		return Shape(id, Color(color), std::make_unique<Circle>(params));
	}
	else if (type == "rectangle")
	{
		return Shape(id, Color(color), std::make_unique<Rectangle>(params));
	}
	else if (type == "triangle")
	{
		return Shape(id, Color(color), std::make_unique<Triangle>(params));
	}
	else if (type == "line")
	{
		return Shape(id, Color(color), std::make_unique<Line>(params));
	}
	else if (type == "text")
	{
		return Shape(id, Color(color), std::make_unique<TextFigure>(params));
	}
	else
	{
		throw std::invalid_argument("Unknown type");
	}
}

int Picture::FindIndexById(const std::string& id)
{
	int index = -1;

	for (int i = 0; i < m_shapes.size(); i++)
	{
		if (m_shapes[i]->GetId() == id)
		{
			index = i;
			break;
		}
	}

	return index;
}
