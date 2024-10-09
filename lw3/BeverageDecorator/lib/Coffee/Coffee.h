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
	Latte(unsigned int size = 1)
		: m_size(size){};
	std::string GetDescription() const override;
	double GetCost() const override;

private:
	unsigned int m_size;
};

class Cappuccino : public Coffee
{
public:
	Cappuccino(unsigned int size = 1)
		: m_size(size){};
	std::string GetDescription() const override;
	double GetCost() const override;

private:
	unsigned int m_size;
};

} // namespace Coffee
