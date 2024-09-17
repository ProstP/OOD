#include "Picture.h"
#include "../DrawingStrategy/Imp/Circle/DrawCircle.h"
#include "../DrawingStrategy/Imp/Line/DrawLine.h"
#include "../DrawingStrategy/Imp/Rectangle/DrawRectangle.h"
#include "../DrawingStrategy/Imp/Text/DrawText.h"
#include "../DrawingStrategy/Imp/Traingle/DrawTriangle.h"
#include <string>

void Picture::AddShape(const std::string& id, const std::string& color, const std::string& type, const std::string& params)
{
	IsIdUsed(id);
	Shape shape(id, Color(color), CreateDrawingStrategyByShapeType(type, params));

	m_shapes.push_back(std::make_unique<Shape>(shape));
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
		out << m_shapes[i]->ToString();
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

	m_shapes[index]->SetDrawingStrategy(CreateDrawingStrategyByShapeType(type, params));
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

void Picture::SetCanvas(std::unique_ptr<ICanvas>&& canvas)
{
	m_canvas = std::move(canvas);
}

Picture::~Picture()
{
	m_canvas = nullptr;
}

IDrawingStrategy Picture::CreateDrawingStrategyByShapeType(const std::string& type, const std::string& params)
{
	if (type == "circle")
	{
		return DrawCircle(params);
	}
	else if (type == "rectangle")
	{
		return DrawRectangle(params);
	}
	else if (type == "triangle")
	{
		return DrawTriangle(params);
	}
	else if (type == "line")
	{
		return DrawLine(params);
	}
	else if (type == "text")
	{
		return DrawTextStrategy(params);
	}
	else
	{
		throw std::invalid_argument("Unknown type");
	}
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
