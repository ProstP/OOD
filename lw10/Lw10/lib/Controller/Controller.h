#pragma once
#include "../Model/ShapeStore.h"

using namespace Types;

enum class Vertices
{
	UL,
	UR,
	DL,
	DR,
	NONE
};

class Controller
{
public:
	Controller(Model::ShapeStore& store)
		: m_store(store)
	{
	}

	void CreateRectangle();
	void CreateTriangle();
	void CreateEllipse();
	void DragShapeTo(Point point);
	void DeleteShape();
	void Select(Point point);
	int GetIndexOfSelected() const;
	void StartResize(Vertices vert, Point mousePos);
	void Resize(Point point);
	void EndResize();

private:
	Model::ShapeStore& m_store;
	int m_selected = -1;
	Point m_oldMousePos = { 0, 0 };

	Vertices m_resizeVert = Vertices::NONE;
};
