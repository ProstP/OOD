#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

class FileUtils
{
public:
	static std::string GetParantPath(const std::string path)
	{
		return std::filesystem::path(path).parent_path().string();
	}

	static void CopyFiles(const std::string& fromPath, const std::string& toPath)
	{
		std::filesystem::path from(fromPath);
		std::filesystem::path to(toPath);

		std::filesystem::path toDir = to.parent_path();
		if (!toDir.empty() && !std::filesystem::exists(toDir))
		{
			std::filesystem::create_directories(toDir);
		}

		std::filesystem::copy(from, to, std::filesystem::copy_options::overwrite_existing);
	}
};
