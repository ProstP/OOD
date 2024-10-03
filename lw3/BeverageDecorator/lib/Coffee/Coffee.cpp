#include "Coffee.h"

std::string Coffee::Coffee::GetDescription() const
{
	return "Coffee";
}

double Coffee::Coffee::GetCost() const
{
	return 60;
}

std::string Coffee::Latte::GetDescription() const
{
	return "Latte";
}

double Coffee::Latte::GetCost() const
{
	return 90;
}

std::string Coffee::Cappuccino::GetDescription() const
{
	return "Cappuccino";
}

double Coffee::Cappuccino::GetCost() const
{
	return 80;
}

std::string Coffee::DoubleLatte::GetDescription() const
{
	return "Double latte";
}

double Coffee::DoubleLatte::GetCost() const
{
	return 130;
}

std::string Coffee::DoubleCappuccino::GetDescription() const
{
	return "Double cappuccino";
}

double Coffee::DoubleCappuccino::GetCost() const
{
	return 120;
}
