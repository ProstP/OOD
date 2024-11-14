#pragma once
#include "../GraphicCanvas/Canvas.h"
#include <sstream>
#include "../Shape/Shapes.h"

class CommandHandler
{
public:
	CommandHandler(GraphicLib::GraphicCanvas& canvas, Shapes::Slide& slide)
		: m_canvas(canvas)
		, m_slide(slide)
		, m_currentShape(slide.GetShapes()){};
	void Handle(std::istream& in, std::ostream& out);

private:
	GraphicLib::GraphicCanvas& m_canvas;
	Shapes::Slide& m_slide;
	std::shared_ptr<Shapes::IShape> m_currentShape;

	void DefineCommand(const std::string& command, std::ostream& out);
	void AddShapeCommand(std::stringstream& iss, std::ostream& out);
	void AddGroupCommand(std::stringstream& iss, std::ostream& out);
	void RemoveShapeCommand(std::stringstream& iss, std::ostream& out);
	void SetFrameCommand(std::stringstream& iss, std::ostream& out);
	void SetOutlineCommand(std::stringstream& iss, std::ostream& out);
	void SetFillCommand(std::stringstream& iss, std::ostream& out);
	void GetChildCommand(std::stringstream& iss, std::ostream& out);
	void StatusCommand(std::ostream& out);
	void HelpCommand(std::ostream& out);
	void SetBackground(std::stringstream& iss);
	void UpToTreeCommand(std::stringstream& iss, std::ostream& out);
	void DrawCommand();
	void PrintColor(RGBAColor color, std::ostream& out);
};
