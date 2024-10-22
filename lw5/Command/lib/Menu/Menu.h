#pragma once
#include <functional>
#include <iostream>
#include <vector>

namespace Menu
{

class Menu
{
public:
	void AddItem(const std::string& shortcut, const std::string& description, std::function<void(std::istream&)> command);
	void Run();
	void ShowInstructions();
	void Exit();

private:
	struct Item
	{
		std::string shortcut;
		std::string description;
		std::function<void(std::istream&)> command;
	};

	void ExecuteCommand(const std::string& command);

	std::vector<Item> m_items;
	bool m_isExit = false;
};

} // namespace Menu
