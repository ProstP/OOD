#include "CommandHandler.h"
#include "../SimpleShapes/SimpleShapes.h"
#include <cstdint>
#include <iomanip>
#include <string>

const std::string EXIT_COMMAND = "...";
const std::string ADD_SHAPE_COMMAND = "AddShape";
const std::string ADD_GROUP_COMMAND = "AddGroup";
const std::string REMOVE_SHAPE_COMMAND = "Remove";
const std::string SET_FRAME_COMMAND = "SetFrame";
const std::string SET_OUTLINE_COMMAND = "SetOutline";
const std::string SET_FILL_COMMAND = "SetFill";
const std::string GET_CHILD_COMMAND = "Get";
const std::string STATUS_COMMAND = "Status";
const std::string HELP_COMMAND = "Help";
const std::string UP_TO_TREE_COMMAND = "Up";
const std::string DRAW_COMMAND = "Draw";

void CommandHandler::Handle(std::istream& in, std::ostream& out)
{
	HelpCommand(out);

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
			out << e.what() << std::endl
				<< std::endl;
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
	else if (commandName == REMOVE_SHAPE_COMMAND)
	{
		RemoveShapeCommand(iss, out);
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
	else if (commandName == STATUS_COMMAND)
	{
		StatusCommand(out);
	}
	else if (commandName == HELP_COMMAND)
	{
		HelpCommand(out);
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
	Shapes::Group* group = m_currentShape->GetGroup();
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

	iss >> type >> left >> top >> width >> height >> pos;

	std::shared_ptr<Shapes::IShape> shape;
	if (type == "rectangle")
	{
		shape = std::make_shared<SimpleShapes::Rectangle>(m_currentShape);
	}
	else if (type == "triangle")
	{
		shape = std::make_shared<SimpleShapes::Triangle>(m_currentShape);
	}
	else if (type == "ellipse")
	{
		shape = std::make_shared<SimpleShapes::Ellipse>(m_currentShape);
	}
	else
	{
		throw std::invalid_argument("Unknown type of shape");
	}

	RectD rect{ left, top, width, height };
	shape->SetFrame(rect);

	group->InsertShape(shape, pos);

	out << "Shape was created" << std::endl
		<< std::endl;
}

void CommandHandler::AddGroupCommand(std::stringstream& iss, std::ostream& out)
{
	Shapes::Group* group = m_currentShape->GetGroup();
	if (group == nullptr)
	{
		throw std::invalid_argument("Current shape not group");
	}

	double left;
	double top;
	double width;
	double height;
	int pos;

	iss >> left >> top >> width >> height >> pos;

	RectD rect{ left, top, width, height };

	std::shared_ptr<Shapes::Group> ptr = std::make_shared<Shapes::Group>(m_currentShape);
	std::shared_ptr<Shapes::IShape> newGroup = std::make_shared<Shapes::Group>(m_currentShape);

	newGroup->SetFrame(rect);
	group->InsertShape(newGroup, pos);

	out << "Group was created" << std::endl
		<< std::endl;
}

void CommandHandler::RemoveShapeCommand(std::stringstream& iss, std::ostream& out)
{
	auto group = m_currentShape->GetGroup();
	if (group == nullptr)
	{
		throw std::invalid_argument("Current shape not group");
	}

	int index;

	iss >> index;

	group->RemoveShapeAtIndex(index);

	out << "Shape was remove" << std::endl;
}

void CommandHandler::SetFrameCommand(std::stringstream& iss, std::ostream& out)
{
	double left;
	double top;
	double width;
	double height;

	iss >> left >> top >> width >> height;

	RectD rect{ left, top, width, height };

	m_currentShape->SetFrame(rect);

	out << "Frame was changed" << std::endl
		<< std::endl;
}

void CommandHandler::SetOutlineCommand(std::stringstream& iss, std::ostream& out)
{
	std::string isEnableStr;
	std::string colorStr;
	int thickness;

	iss >> isEnableStr >> colorStr >> thickness;

	bool isEnable = isEnableStr == "true" || isEnableStr == "1" ? true : false;

	uint32_t color = static_cast<uint32_t>(std::stoul(colorStr, nullptr, 16));

	Shapes::StyleWithThickness style;

	style.Enable(isEnable);
	if (isEnable)
	{
		style.SetColor(color);
		style.SetThickness(thickness);
	}

	m_currentShape->SetOutlineStyle(std::make_shared<Shapes::StyleWithThickness>(style));

	out << "Outline style was changed" << std::endl
		<< std::endl;
}

void CommandHandler::SetFillCommand(std::stringstream& iss, std::ostream& out)
{
	std::string isEnableStr;
	std::string colorStr;

	iss >> isEnableStr >> colorStr;

	bool isEnable = isEnableStr == "true" || isEnableStr == "1" ? true : false;

	uint32_t color = static_cast<uint32_t>(std::stoul(colorStr, nullptr, 16));

	Shapes::Style style;
	style.Enable(isEnable);
	if (isEnable)
	{
		style.SetColor(color);
	}

	m_currentShape->SetFillStyle(std::make_shared<Shapes::Style>(style));

	out << "Fill style was changed" << std::endl
		<< std::endl;
}

void CommandHandler::GetChildCommand(std::stringstream& iss, std::ostream& out)
{
	auto group = m_currentShape->GetGroup();
	if (group == nullptr)
	{
		throw std::invalid_argument("Current shape not group");
	}

	int pos;
	iss >> pos;

	m_currentShape = group->GetShapeAtIndex(pos);

	out << "Current shape was changed" << std::endl
		<< std::endl;
}

void CommandHandler::StatusCommand(std::ostream& out)
{
	out << std::endl
		<< "Status: " << std::endl;
	auto group = m_currentShape->GetGroup();
	if (group == nullptr)
	{
		out << "Current shape is not group" << std::endl;
	}
	else
	{
		out << "Current shape is group" << std::endl;
		out << "Child count: " << group->GetShapeCount() << std::endl;
	}

	RectD frame = m_currentShape->GetFrame();

	out << "Frame:" << std::endl;
	out << "  Left: " << frame.left << std::endl;
	out << "  Top: " << frame.top << std::endl;
	out << "  Width: " << frame.width << std::endl;
	out << "  Height: " << frame.height << std::endl;

	auto outlineStyle = m_currentShape->GetOutlineStyle();
	if (outlineStyle != nullptr)
	{
		out << "  Outline style:" << std::endl;
		out << "    Enable: " << (outlineStyle->IsEnable() ? "true" : "false") << std::endl;
		out << "    Color: ";
		auto outLineColor = outlineStyle->GetColor();
		if (outLineColor == std::nullopt)
		{
			out << "empty";
		}
		else
		{
			PrintColor(outLineColor.value(), out);
		}
		out << std::endl;
		out << "    Thickness: " << outlineStyle->GetThickness() << std::endl;
	}

	auto fillStyle = m_currentShape->GetFillStyle();
	if (fillStyle != nullptr)
	{
		out << "  Fill style:" << std::endl;
		out << "    Enable: " << (fillStyle->IsEnable() ? "true" : "false") << std::endl;
		out << "    Color: ";
		auto fillColor = fillStyle->GetColor();
		if (fillColor == std::nullopt)
		{
			out << "empty";
		}
		else
		{
			PrintColor(fillColor.value(), out);
		}
		out << std::endl;
	}
	out << std::endl;
}

void CommandHandler::HelpCommand(std::ostream& out)
{
	out << std::endl
		<< "Commands:" << std::endl;
	out << "  "
		<< "Exit: " << EXIT_COMMAND << std::endl;
	out << "  " << ADD_SHAPE_COMMAND << " <type> <left> <top> <width> <height> <pos>" << std::endl;
	out << "  " << ADD_GROUP_COMMAND << " <left> <top> <width> <height> <pos>" << std::endl;
	out << "  " << REMOVE_SHAPE_COMMAND << " <index>" << std::endl;
	out << "  " << SET_FRAME_COMMAND << " <left> <top> <width> <height> <pos>" << std::endl;
	out << "  " << SET_OUTLINE_COMMAND << " <isEnable> <color(0x00000000)> <thickness>" << std::endl;
	out << "  " << SET_FILL_COMMAND << " <isEnable> <color(0x00000000)>" << std::endl;
	out << "  " << GET_CHILD_COMMAND << " <pos>" << std::endl;
	out << "  " << STATUS_COMMAND << std::endl;
	out << "  " << UP_TO_TREE_COMMAND << std::endl;
	out << "  " << DRAW_COMMAND << std::endl
		<< std::endl;
}

void CommandHandler::UpToTreeCommand(std::stringstream& iss, std::ostream& out)
{
	if (m_currentShape->GetParent() == nullptr)
	{
		throw std::invalid_argument("Can't up to tree, already on root");
	}

	m_currentShape = m_currentShape->GetParent();

	out << "Up to tree" << std::endl
		<< std::endl;
}

void CommandHandler::DrawCommand(std::stringstream& iss, std::ostream& out)
{
	m_slide.DrawBackground(m_canvas);
	m_slide.GetShapes()->Draw(m_canvas);

	out << std::endl
		<< "Slide was drawing" << std::endl
		<< std::endl;
}

void CommandHandler::PrintColor(RGBAColor color, std::ostream& out)
{
	uint8_t a = color;
	uint8_t b = color >> 8;
	uint8_t g = color >> 16;
	uint8_t r = color >> 24;

	out << "(#" << std::hex
		<< std::setw(2) << std::setfill('0') << static_cast<int>(r)
		<< std::setw(2) << std::setfill('0') << static_cast<int>(g)
		<< std::setw(2) << std::setfill('0') << static_cast<int>(b)
		<< std::setw(2) << std::setfill('0') << static_cast<int>(a)
		<< std::dec << ")";
}
