#pragma once
#include "../Beverage/IBeverage.h"
#include <string>

namespace Tea
{

class Tea : public Beverage::IBeverage
{
public:
	std::string GetDescription() const override;
	double GetCost() const override;
};

class BlackTea : public Tea
{
public:
	std::string GetDescription() const override;
};

class GreenTea : Tea
{
public:
	std::string GetDescription() const override;
};

class IvanTea : public Tea
{
public:
	std::string GetDescription() const override;
};

class WhiteTea : public Tea
{
public:
	std::string GetDescription() const override;
};

} // namespace Tea
