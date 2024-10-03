#include "MilkShake.h"

std::string MilkShake::MilkShake::GetDescription() const
{
	return "Milk shake";
}

double MilkShake::MilkShake::GetCost() const
{
	return 60;
}

std::string MilkShake::SmallMilkShake::GetDescription() const
{
	return "Small milk shake";
}

double MilkShake::SmallMilkShake::GetCost() const
{
	return 50;
}

std::string MilkShake::LargeMilkShake::GetDescription() const
{
	return "Large milk shake";
}

double MilkShake::LargeMilkShake::GetCost() const
{
	return 80;
}
