#include "Controller.h"

const Types::Rect BASE_RECT = { 280, 200, 80, 80 };

void Controller::CreateRectangle()
{
	m_store.AddShape("rectangle");
	m_store.GetAt(m_store.GetShapesCount() - 1)->SetRect(BASE_RECT);
}

void Controller::CreateTriangle()
{
	m_store.AddShape("triangle");
	m_store.GetAt(m_store.GetShapesCount() - 1)->SetRect(BASE_RECT);
}

void Controller::CreateEllipse()
{
	m_store.AddShape("ellipse");
	m_store.GetAt(m_store.GetShapesCount() - 1)->SetRect(BASE_RECT);
}

void Controller::DragShapeTo(Point point)
{
	if (m_selected < 0 || m_selected >= m_store.GetShapesCount())
	{
		return;
	}

	int dx = point.x - m_oldMousePos.x;
	int dy = point.y - m_oldMousePos.y;

	m_oldMousePos = point;

	m_store.GetAt(m_selected)->Move(dx, dy);
}

void Controller::DeleteShape()
{
	if (m_selected < 0 || m_selected >= m_store.GetShapesCount())
	{
		return;
	}

	m_store.DeleteAtIndex(m_selected);
	m_selected = -1;
}

void Controller::Select(Point point)
{
	m_selected = -1;

	for (int i = 0; i < m_store.GetShapesCount(); i++)
	{
		Rect rect = m_store.GetAt(i)->GetRect();

		if (rect.left <= point.x && point.x <= rect.left + static_cast<int>(rect.width)
			&& rect.top <= point.y && point.y <= rect.top + static_cast<int>(rect.height))
		{
			m_selected = i;
			m_oldMousePos = point;
		}
	}
}

int Controller::GetIndexOfSelected() const
{
	return m_selected;
}

void Controller::StartResize(Vertices vert, Point mousePos)
{
	if (m_selected == -1)
	{
		return;
	}

	m_resizeVert = vert;
	m_oldMousePos = mousePos;
}

void Controller::Resize(Point point)
{
	if (m_selected == -1 && m_resizeVert == Vertices::NONE)
	{
		return;
	}

	int dx = point.x - m_oldMousePos.x;
	int dy = point.y - m_oldMousePos.y;

	m_oldMousePos = point;

	Rect rect = m_store.GetAt(m_selected)->GetRect();
	switch (m_resizeVert)
	{
	case Vertices::UL: {
		int right = rect.left + rect.width;
		if (point.x + 4 < right)
		{
			rect.left += dx;
			rect.width = right - rect.left;
		}

		int bottom = rect.top + rect.height;
		if (point.y - 56 < bottom)
		{
			rect.top += dy;
			rect.height = bottom - rect.top;
		}
	}
	break;
	case Vertices::UR: {
		int bottom = rect.top + rect.height;
		if (point.y - 56 < bottom)
		{
			rect.top += dy;
			rect.height = bottom - rect.top;
		}

		if (point.x - 4 > rect.left)
		{
			rect.width += dx;
		}
	}
	break;
	case Vertices::DL: {
		int right = rect.left + rect.width;
		if (point.x + 4 < right)
		{
			rect.left += dx;
			rect.width = right - rect.left;
		}

		if (point.y - 64 > rect.top)
		{
			rect.height += dy;
		}
	}
	break;
	case Vertices::DR: {
		if (point.x - 4 > rect.left)
		{
			rect.width += dx;
		}

		if (point.y - 64 > rect.top)
		{
			rect.height += dy;
		}
	}
	break;
	case Vertices::NONE:
	default:
		break;
	}

	m_store.GetAt(m_selected)->SetRect(rect);
}

void Controller::EndResize()
{
	m_resizeVert = Vertices::NONE;
}
