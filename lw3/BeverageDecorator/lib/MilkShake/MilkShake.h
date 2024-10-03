#pragma once
#include "../Beverage/IBeverage.h"

namespace MilkShake
{

class MilkShake : public Beverage::IBeverage
{
public:
	std::string GetDescription() const override;
	double GetCost() const override;
};

class SmallMilkShake : public MilkShake
{
public:
	std::string GetDescription() const override;
	double GetCost() const override;
};

class LargeMilkShake : public MilkShake
{
public:
	std::string GetDescription() const override;
	double GetCost() const override;
};

} // namespace MilkShake
