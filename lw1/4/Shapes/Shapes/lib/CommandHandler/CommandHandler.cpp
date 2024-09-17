#include "CommandHandler.h"
#include "Commands.h"
#include <set>
#include <string>

CommandHandler::CommandHandler(Picture* picture)
{
	m_picture = picture;
	picture = nullptr;
}

void CommandHandler::Handle(std::istream& in, std::ostream& out)
{
	out << "Enter command:" << std::endl;
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
			<< "Shape was created" << std::endl << std::endl;
	}
	else if (command.find(MOVE_SHAPE) != std::string::npos)
	{
		MoveShapeCommand(command);
		out << std::endl
			<< "Shape was moved" << std::endl << std::endl;
	}
	else if (command.find(MOVE_PICTURE) != std::string::npos)
	{
		MovePictureCommand(command);
		out << std::endl
			<< "Picture was moved" << std::endl << std::endl;
	}
	else if (command.find(DELETE_SHAPE) != std::string::npos)
	{
		DeleteShapeCommand(command);
		out << std::endl
			<< "Shape was deleted" << std::endl << std::endl;
	}
	else if (command.find(LIST) != std::string::npos)
	{
		ListCommand(command, out);
		out << std::endl
			<< "List getted" << std::endl << std::endl;
	}
	else if (command.find(CHANGE_COLOR) != std::string::npos)
	{
		ChangeColorCommand(command);
		out << std::endl
			<< "Color was changed" << std::endl << std::endl;
	}
	else if (command.find(CHANGE_SHAPE) != std::string::npos)
	{
		ChangeShapeCommand(command);
		out << std::endl
			<< "Shape was changed" << std::endl << std::endl;
	}
	else if (command.find(DRAW_SHAPE) != std::string::npos)
	{
		DrawShapeCommand(command);
		out << std::endl
			<< "Shape was drawed" << std::endl << std::endl;
	}
	else if (command.find(DRAW_PICTURE) != std::string::npos)
	{
		DrawPictureCommand(command);
		out << std::endl
			<< "Picture was drawed" << std::endl << std::endl;
	}
}

void CommandHandler::AddShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + ADD_SHAPE + ")\\s+(\\w+)\\s+#([0-9a-f]{6})\\s+(\\w+)\\s+(.+)$", std::regex_constants::icase), m, command);
	//std::cout << m[2].str() << "!" << std::endl;
	//std::cout << m[3].str() << "!" << std::endl;
	//std::cout << m[4].str() << "!" << std::endl;
	//std::cout << m[5].str() << "!" << std::endl;
	m_picture->AddShape(m[2].str(), m[3].str(), m[4].str(), m[5].str());
}

void CommandHandler::MoveShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + MOVE_SHAPE + ")\\s+(\\w+)\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)$"), m, command);
	//std::cout << m[2].str() << "!" << std::endl;
	//std::cout << m[3].str() << "!" << std::endl;
	//std::cout << m[4].str() << "!" << std::endl;
	double dx;
	double dy;
	try
	{
		dx = std::stod(m[3].str());
		dy = std::stod(m[4].str());
	}
	catch (...)
	{
		throw std::invalid_argument("Values to move shape must be digit");
	}
	m_picture->MoveShape(m[2].str(), dx, dy);
}

void CommandHandler::MovePictureCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + MOVE_PICTURE + ")\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)$"), m, command);
	//std::cout << m[2].str() << "!" << std::endl;
	//std::cout << m[3].str() << "!" << std::endl;
	double dx;
	double dy;
	try
	{
		dx = std::stod(m[2].str());
		dy = std::stod(m[3].str());
	}
	catch (...)
	{
		throw std::invalid_argument("Values to move shape must be digit");
	}
	m_picture->MovePicture(dx, dy);
}

void CommandHandler::DeleteShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + DELETE_SHAPE + ")\\s+(\\w+)$"), m, command);
	//std::cout << m[2].str() << "!" << std::endl;
	m_picture->DeleteShape(m[2].str());
}

void CommandHandler::ListCommand(const std::string& command, std::ostream& out)
{
	std::smatch m;
	ParseCommand(std::regex("^" + LIST + "$"), m, command);
	//std::cout << "List" << std::endl;
	m_picture->List(out);
}

void CommandHandler::ChangeColorCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + CHANGE_COLOR + ")\\s+(\\w+)\\s+#([0-9a-f]{6})$", std::regex_constants::icase), m, command);
	//std::cout << m[2].str() << "!" << std::endl;
	//std::cout << m[3].str() << "!" << std::endl;
	m_picture->ChangeColor(m[2].str(), m[3].str());
}

void CommandHandler::ChangeShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + CHANGE_SHAPE + ")\\s+(\\w+)\\s+(\\w+)\\s+(.+)$"), m, command);
	//std::cout << m[2].str() << "!" << std::endl;
	//std::cout << m[3].str() << "!" << std::endl;
	//std::cout << m[4].str() << "!" << std::endl;
	m_picture->ChangeShape(m[2].str(), m[3].str(), m[4].str());
}

void CommandHandler::DrawShapeCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + DRAW_SHAPE + ")\\s+(\\w+)$"), m, command);
	//std::cout << m[2].str() << "!";
	m_picture->DrawShape(m[2].str());
}

void CommandHandler::DrawPictureCommand(const std::string& command)
{
	std::smatch m;
	ParseCommand(std::regex("^(" + DRAW_PICTURE + ")$"), m, command);
	//std::cout << "draw picture";
	m_picture->DrawPicture();
}

void CommandHandler::ParseCommand(const std::regex& pattern, std::smatch& match, const std::string& command)
{
	if (!std::regex_match(command, match, pattern))
	{
		throw std::invalid_argument("Invalid command");
	}
}

void CommandHandler::CheckIdWithReservedWords(const std::string& id)
{
	const std::set<std::string> reservedWords = {
		ADD_SHAPE, MOVE_SHAPE, MOVE_PICTURE, DELETE_SHAPE, LIST, CHANGE_COLOR, CHANGE_SHAPE, DRAW_SHAPE, DRAW_PICTURE
	};

	if (reservedWords.contains(id))
	{
		throw std::invalid_argument("Id alredy reserved");
	}
}
