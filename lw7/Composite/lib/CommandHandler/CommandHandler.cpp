#include "CommandHandler.h"
#include "../SimpleShapes/SimpleShapes.h"
#include <string>

const std::string EXIT_COMMAND = "...";
const std::string ADD_SHAPE_COMMAND = "AddShape";
const std::string ADD_GROUP_COMMAND = "AddGroup";
const std::string SET_FRAME_COMMAND = "SetFrame";
const std::string SET_OUTLINE_COMMAND = "SetOutline";
const std::string SET_FILL_COMMAND = "SetFill";
const std::string GET_CHILD_COMMAND = "GetChild";
const std::string UP_TO_TREE_COMMAND = "Up";
const std::string DRAW_COMMAND = "Draw";

void CommandHandler::Handle(std::istream& in, std::ostream& out)
{
	std::string command;

	while (std::getline(in, command))
	{
		if (command == EXIT_COMMAND)
		{
			break;
		}

		try
		{
			DefineCommand(command, out);
		}
		catch (const std::exception& e)
		{
			out << e.what() << std::endl;
		}
	}
}

void CommandHandler::DefineCommand(const std::string& command, std::ostream& out)
{
	std::stringstream iss(command);

	std::string commandName;
	iss >> commandName;

	if (commandName == ADD_SHAPE_COMMAND)
	{
		AddShapeCommand(iss, out);
	}
	else if (commandName == ADD_GROUP_COMMAND)
	{
		AddGroupCommand(iss, out);
	}
	else if (commandName == SET_FRAME_COMMAND)
	{
		SetFrameCommand(iss, out);
	}
	else if (commandName == SET_OUTLINE_COMMAND)
	{
		SetOutlineCommand(iss, out);
	}
	else if (commandName == SET_FILL_COMMAND)
	{
		SetFillCommand(iss, out);
	}
	else if (commandName == GET_CHILD_COMMAND)
	{
		GetChildCommand(iss, out);
	}
	else if (commandName == UP_TO_TREE_COMMAND)
	{
		UpToTreeCommand(iss, out);
	}
	else if (commandName == DRAW_COMMAND)
	{
		DrawCommand(iss, out);
	}
	else
	{
		throw std::invalid_argument("Unknown command");
	}
}

void CommandHandler::AddShapeCommand(std::stringstream& iss, std::ostream& out)
{
	Shapes::Group* group = m_currentShape.GetGroup();
	if (group == nullptr)
	{
		throw std::invalid_argument("Current shape not group");
	}

	std::string type;
	double left;
	double top;
	double width;
	double height;
	int pos;

	iss >> type >> left >> top >> width >> height;

	RectD rect{ left, top, width, height };

	std::shared_ptr<Shapes::IShape> shape;
	if (type == "rectangle")
	{
		shape = std::make_shared<SimpleShapes::Rectangle>(*group);
	}
	else if (type == "triangle")
	{
		shape = std::make_shared<SimpleShapes::Triangle>(*group);
	}
	else if (type == "ellipse")
	{
		shape = std::make_shared<SimpleShapes::Ellipse>(*group);
	}
	else
	{
		throw std::invalid_argument("Unknown type of shape");
	}

	shape->SetFrame(rect);

	group->InserShape(shape, pos);

	out << "Shape was created" << std::endl;
}

void CommandHandler::AddGroupCommand(std::stringstream& iss, std::ostream& out)
{
	Shapes::Group* group = m_currentShape.GetGroup();
	if (group == nullptr)
	{
		throw std::invalid_argument("Current shape not group");
	}

	double left;
	double top;
	double width;
	double height;
	int pos;

	iss >> left >> top >> width >> height;

	RectD rect{ left, top, width, height };

	std::shared_ptr<Shapes::IShape> newGroup = std::make_shared<Shapes::Group>(group);

	newGroup->SetFrame(rect);
	group->InserShape(newGroup, pos);

	out << "Group was created" << std::endl;
}

void CommandHandler::SetFrameCommand(std::stringstream& iss, std::ostream& out)
{
	double left;
	double top;
	double width;
	double height;

	iss >> left >> top >> width >> height;

	RectD rect{ left, top, width, height };

	m_currentShape.SetFrame(rect);

	out << "Frame was changed" << std::endl;
}

void CommandHandler::SetOutlineCommand(std::stringstream& iss, std::ostream& out)
{
	bool isEnable;
	uint32_t color;
	int thickness;

	iss >> isEnable >> color >> thickness;

	Shapes::StyleWithThickness style;

	style.Enable(isEnable);
	if (isEnable)
	{
		style.SetColor(color);
		style.SetThickness(thickness);
	}

	m_currentShape.SetOutlineStyle(style);

	out << "Outline style was changed" << std::endl;
}

void CommandHandler::SetFillCommand(std::stringstream& iss, std::ostream& out)
{
	bool isEnable;
	uint32_t color;

	iss >> isEnable >> color;
	Shapes::Style style;
	style.Enable(isEnable);
	if (isEnable)
	{
		style.SetColor(color);
	}

	m_currentShape.SetFillStyle(style);

	out << "Fill style was changed" << std::endl;
}

void CommandHandler::GetChildCommand(std::stringstream& iss, std::ostream& out)
{
	auto group = m_currentShape.GetGroup();
	if (group == nullptr)
	{
		throw std::invalid_argument("Current shape not group");
	}

	int pos;
	iss >> pos;

	group->GetShapeAtIndex(pos);

	out << "Current shape was changed" << std::endl;
}

void CommandHandler::UpToTreeCommand(std::stringstream& iss, std::ostream& out)
{
	m_currentShape = *m_currentShape.GetParent();

	out << "Up to tree" << std::endl;
}

void CommandHandler::DrawCommand(std::stringstream& iss, std::ostream& out)
{
	m_slide.DrawBackground(m_canvas);
	m_slide.GetShapes()->Draw(m_canvas);

	out << "Slide was drawing" << std::endl;
}
