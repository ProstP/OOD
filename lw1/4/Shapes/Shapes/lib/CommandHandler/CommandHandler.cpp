#include "CommandHandler.h"
#include "Commands.h"
#include <string>

CommandHandler::CommandHandler(Picture& picture)
{
	m_picture = &picture;
}

void CommandHandler::Handle(std::istream& in, std::ostream& out)
{
	std::string command;

	while (std::getline(in, command))
	{
		if (command == "exit")
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

CommandHandler::~CommandHandler()
{
	m_picture = nullptr;
}

void CommandHandler::DefineCommand(const std::string& command, std::ostream& out)
{
	if (command.find(ADD_SHAPE) != std::string::npos)
	{
		AddShapeCommand(command);
		out << std::endl
			<< "Shape was created" << std::endl;
	}
	else if (command.find(MOVE_SHAPE) != std::string::npos)
	{
		MoveShapeCommand(command);
		out << std::endl
			<< "Shape was moved" << std::endl;
	}
	else if (command.find(MOVE_PICTURE) != std::string::npos)
	{
		MovePictureCommand(command);
		out << std::endl
			<< "Picture was moved" << std::endl;
	}
	else if (command.find(DELETE_SHAPE) != std::string::npos)
	{
		DeleteShapeCommand(command);
		out << std::endl
			<< "Shape was deleted" << std::endl;
	}
	else if (command.find(LIST) != std::string::npos)
	{
		ListCommand(command, out);
		out << std::endl
			<< "List getted" << std::endl;
	}
	else if (command.find(CHANGE_COLOR) != std::string::npos)
	{
		ChangeColorCommand(command);
		out << std::endl
			<< "Color was changed" << std::endl;
	}
	else if (command.find(CHANGE_SHAPE) != std::string::npos)
	{
		ChangeShapeCommand(command);
		out << std::endl
			<< "Shape was changed" << std::endl;
	}
	else if (command.find(DRAW_SHAPE) != std::string::npos)
	{
		DrawShapeCommand(command);
		out << std::endl
			<< "Shape was drawed" << std::endl;
	}
	else if (command.find(DRAW_PICTURE) != std::string::npos)
	{
		DrawPictureCommand(command);
		out << std::endl
			<< "Picture was drawed" << std::endl;
	}
}

void CommandHandler::AddShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + ADD_SHAPE + ")\\s+(\\w+)\\s+#([0-9a-f]{6})\\s+(\\w+)\\s+(.+)$", std::regex_constants::icase), m, command);
	std::cout << m[2].str() << "!" << std::endl;
	std::cout << m[3].str() << "!" << std::endl;
	std::cout << m[4].str() << "!" << std::endl;
	std::cout << m[5].str() << "!" << std::endl;
	//m_picture->AddShape();
}

void CommandHandler::MoveShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + MOVE_SHAPE + ")\\s+(\\w+)\\s+([\\d\.]+)\\s+([\\d\.]+)$"), m, command);
	std::cout << m[2].str() << "!" << std::endl;
	std::cout << m[3].str() << "!" << std::endl;
	std::cout << m[4].str() << "!" << std::endl;
	//m_picture->MoveShape();
}

void CommandHandler::MovePictureCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + MOVE_PICTURE + ")\\s+([\\d\.]+)\\s+([\\d\.]+)$"), m, command);
	std::cout << m[2].str() << "!" << std::endl;
	std::cout << m[3].str() << "!" << std::endl;
	//m_picture->MovePicture();
}

void CommandHandler::DeleteShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + DELETE_SHAPE + ")\\s+(\\w+)$"), m, command);
	std::cout << m[2].str() << "!" << std::endl;
	//m_picture->DeleteShape();
}

void CommandHandler::ListCommand(const std::string& command, std::ostream& out)
{
	std::smatch m;
	ParseCommand(std::regex("^" + LIST + "$"), m, command);
	std::cout << "List" << std::endl;
	//m_picture->List(out);
}

void CommandHandler::ChangeColorCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^("+CHANGE_COLOR+")\\s+(\\w+)\\s+#([0-9a-f]{6})$", std::regex_constants::icase), m, command);
	std::cout << m[2].str() << "!" << std::endl;
	std::cout << m[3].str() << "!" << std::endl;
	//m_picture->ChangeColor();
}

void CommandHandler::ChangeShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^("+ CHANGE_SHAPE+")\\s+(\\w+)\\s+(\\w+)\\s+(.+)$"), m, command);
	std::cout << m[2].str() << "!" << std::endl;
	std::cout << m[3].str() << "!" << std::endl;
	std::cout << m[4].str() << "!" << std::endl;
	//m_picture->ChangeShape();
}

void CommandHandler::DrawShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(+" + DRAW_SHAPE + ")\\s+(\\w+)$"), m, command);
	std::cout << m[2].str() << "!";
	//m_picture->DrawShape(m[2].str());
}

void CommandHandler::DrawPictureCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + DRAW_PICTURE + ")$"), m, command);
	std::cout << "draw picture";
	//m_picture->DrawPicture();
}

void CommandHandler::ParseCommand(const std::regex& pattern, std::smatch& match, const std::string& command)
{
	if (!std::regex_match(command, match, pattern))
	{
		throw std::invalid_argument("Unknown command");
	}
}
