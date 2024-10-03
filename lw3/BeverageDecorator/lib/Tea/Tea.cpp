#include "Tea.h"

std::string Tea::Tea::GetDescription() const
{
	return "Tea";
}

double Tea::Tea::GetCost() const
{
	return 30;
}

std::string Tea::BlackTea::GetDescription() const
{
	return "Black tea";
}

std::string Tea::GreenTea::GetDescription() const
{
	return "Green tea";
}

std::string Tea::IvanTea::GetDescription() const
{
	return "Ivan tea";
}

std::string Tea::WhiteTea::GetDescription() const
{
	return "White tea";
}
