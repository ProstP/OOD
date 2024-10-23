#pragma once
#include <iostream>

static std::string GenerateRandomString(size_t length)
{
	const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	std::string randomString;

	srand(static_cast<unsigned int>(time(0)));

	for (size_t i = 0; i < length; ++i)
	{
		randomString += characters[rand() % characters.size()];
	}
	return randomString;
}
