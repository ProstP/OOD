#pragma once
#include "../Beverage/IBeverage.h"

namespace Coffee
{

class Coffee : public Beverage::IBeverage
{
public:
	std::string GetDescription() const override;
	double GetCost() const override;
};

class Latte : public Coffee
{
public:
	std::string GetDescription() const override;
	double GetCost() const override;
};

class Cappuccino : public Coffee
{
	std::string GetDescription() const override;
	double GetCost() const override;
};

class DoubleLatte : public Latte
{
	std::string GetDescription() const override;
	double GetCost() const override;
};

class DoubleCappuccino : public Cappuccino
{
public:
	std::string GetDescription() const override;
	double GetCost() const override;
};

} // namespace Coffee
