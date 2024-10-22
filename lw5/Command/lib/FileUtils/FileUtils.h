#pragma once
#include <fstream>
#include <iostream>

class FileUtils
{
public:
	static std::string GetFileName(const std::string& filePath)
	{
		size_t lastSlashPos = filePath.find_first_of('/');

		if (lastSlashPos != std::string::npos && lastSlashPos != 0)
		{
			return filePath.substr(lastSlashPos + 1);
		}

		return "";
	}

	static void CopyFiles(const std::string& fromName, const std::string& toName)
	{
		std::ifstream from(fromName);
		if (!from.is_open())
		{
			throw std::invalid_argument("Failed to open file");
		}
		std::ofstream to(toName);
		if (!to.is_open())
		{
			throw std::invalid_argument("Failed to open file");
		}

		char buffer[4000];
		while (!from.eof())
		{
			from.read(buffer, sizeof(buffer));
			to.write(buffer, from.gcount());
		}

		from.close();
		to.close();
	}
};
