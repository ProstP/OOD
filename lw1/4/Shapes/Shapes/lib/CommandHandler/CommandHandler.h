#pragma once
#include "../Shapes/Picture.h"
#include <iostream>
#include <regex>

class CommandHandler
{
public:
	CommandHandler(){};
	CommandHandler(Picture& picture);
	void Handle(std::istream& in, std::ostream& out);
	~CommandHandler();

private:
	Picture* m_picture;

	void DefineCommand(const std::string& command, std::ostream& out);
	void AddShapeCommand(const std::string& command);
	void MoveShapeCommand(const std::string& command);
	void MovePictureCommand(const std::string& command);
	void DeleteShapeCommand(const std::string& command);
	void ListCommand(const std::string& command, std::ostream& out);
	void ChangeColorCommand(const std::string& command);
	void ChangeShapeCommand(const std::string& command);
	void DrawShapeCommand(const std::string& command);
	void DrawPictureCommand(const std::string& command);
	void ParseCommand(const std::regex& pattern, std::smatch& match, const std::string& command);
};
