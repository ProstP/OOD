#pragma once
#include <string>

std::string ConvertDoubleToString(double value)
{
	std::string str = std::to_string(value);
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.erase(str.find_last_not_of('.') + 1, std::string::npos);

	return str;
}