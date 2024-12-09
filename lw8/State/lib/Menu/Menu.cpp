#include "Menu.h"
#include <algorithm>
#include <sstream>
#include <string>

void Menu::AddItem(const std::string& shortcut, const std::string& description, std::function<void(std::istream&)> command)
{
	m_items.push_back(Item{ shortcut, description, command });
}

void Menu::Run()
{
	ShowInstructions();

	std::string command;

	while (!m_isExit && std::getline(std::cin, command))
	{
		try
		{
			ExecuteCommand(command);

			std::cout << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void Menu::ShowInstructions()
{
	std::cout << std::endl
			  << "Commands:" << std::endl;

	for (const auto& item : m_items)
	{
		std::cout << item.shortcut << ": " << item.description << std::endl;
	}

	std::cout << std::endl;
}

void Menu::Exit()
{
	m_isExit = true;
}

void Menu::ExecuteCommand(const std::string& command)
{
	std::istringstream iss(command);

	std::string name;
	iss >> name;

	auto iter = std::find_if(m_items.begin(), m_items.end(), [&name](const Item& item) {
		return item.shortcut == name;
	});

	if (iter == m_items.end())
	{
		throw std::invalid_argument("Unknown command " + name);
	}

	iter->command(iss);
}
