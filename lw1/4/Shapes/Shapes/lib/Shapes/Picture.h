#pragma once
#include "Shape.h"
#include <vector>

class Picture
{
public:
	void AddShape(const std::string& id, const std::string& color, const std::string& type, const std::string& params);
	void MoveShape(const std::string& id, double dx, double dy);
	void MovePicture(double dx, double dy);
	void DeleteShape(const std::string& id);
	void List(std::ostream& out) const;
	void ChangeColor(const std::string& id, const std::string& color);
	void ChangeShape(const std::string& id, const std::string& type, const std::string& params);
	void DrawShape(const std::string& id);
	void DrawPicture();
	void SetCanvas(std::unique_ptr<ICanvas>&& canvas);

	~Picture();

private:
	std::unique_ptr<ICanvas> m_canvas;
	std::vector<std::unique_ptr<Shape>> m_shapes;
	IDrawingStrategy CreateDrawingStrategyByShapeType(const std::string& type, const std::string& params);
	void IsIdUsed(const std::string& id);
	int FindIndexById(const std::string& id);
};
