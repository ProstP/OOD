#pragma once
#include "../Canvas/ICanvas.h"
#include <sstream>
#include "../Shape/Shapes.h"

class CommandHandler
{
public:
	CommandHandler(Canvas::ICanvas& canvas, Shapes::Slide& slide)
		: m_canvas(canvas)
		, m_slide(slide)
		, m_currentShape(*slide.GetShapes()){};
	void Handle(std::istream& in, std::ostream& out);

private:
	Canvas::ICanvas& m_canvas;
	Shapes::Slide& m_slide;
	Shapes::IShape& m_currentShape;

	void DefineCommand(const std::string& command, std::ostream& out);
	void AddShapeCommand(std::stringstream& iss, std::ostream& out);
	void AddGroupCommand(std::stringstream& iss, std::ostream& out);
	void SetFrameCommand(std::stringstream& iss, std::ostream& out);
	void SetOutlineCommand(std::stringstream& iss, std::ostream& out);
	void SetFillCommand(std::stringstream& iss, std::ostream& out);
	void GetChildCommand(std::stringstream& iss, std::ostream& out);
	void UpToTreeCommand(std::stringstream& iss, std::ostream& out);
	void DrawCommand(std::stringstream& iss, std::ostream& out);
};
