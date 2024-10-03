#pragma once
#include "../Beverage/IBeverage.h"
#include <iostream>

using namespace Beverage;

namespace Condiment
{

class CondimentDecorator : public IBeverage
{
public:
	std::string GetDescription() const override
	{
		// ќписание декорированного напитка добавл€етс€ к описанию оборачиваемого напитка
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost() const override
	{
		// —тоимость складываетс€ из стоимости добавки и стоимости декорируемого напитка
		return m_beverage->GetCost() + GetCondimentCost();
	}

protected:
	// —тоимость и описание добавки вычисл€етс€ в классах конкретных декораторов
	virtual std::string GetCondimentDescription() const = 0;
	virtual double GetCondimentCost() const = 0;

	CondimentDecorator(IBeveragePtr&& beverage)
		: m_beverage(move(beverage))
	{
	}

private:
	IBeveragePtr m_beverage;
};

class Cinnamon : public CondimentDecorator
{
public:
	Cinnamon(IBeveragePtr&& beverage)
		: CondimentDecorator(move(beverage))
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 20;
	}

	std::string GetCondimentDescription() const override
	{
		return "Cinnamon";
	}
};

class Lemon : public CondimentDecorator
{
public:
	Lemon(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CondimentDecorator(move(beverage))
		, m_quantity(quantity)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 10.0 * m_quantity;
	}
	std::string GetCondimentDescription() const override
	{
		return "Lemon x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};

enum class IceCubeType
{
	Dry, // —ухой лед (дл€ суровых сибирских мужиков)
	Water // ќбычные кубики из воды
};

class IceCubes : public CondimentDecorator
{
public:
	IceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
		: CondimentDecorator(move(beverage))
		, m_quantity(quantity)
		, m_type(type)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		// „ем больше кубиков, тем больше стоимость.
		// —ухой лед стоит дороже

		unsigned int cost = m_type == IceCubeType::Dry ? 10 : 5;
		if (UINT_MAX / cost < m_quantity)
		{
			throw std::out_of_range("Overflow full");
		}

		return cost * m_quantity;
	}
	std::string GetCondimentDescription() const override
	{
		return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
			+ " ice cubes x " + std::to_string(m_quantity) + "; ";
	}

private:
	unsigned m_quantity;
	IceCubeType m_type;
};

enum class SyrupType
{
	Chocolate, // Ўоколадный
	Maple, //  леновый
};

class Syrup : public CondimentDecorator
{
public:
	Syrup(IBeveragePtr&& beverage, SyrupType syrupType)
		: CondimentDecorator(move(beverage))
		, m_syrupType(syrupType)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 15;
	}
	std::string GetCondimentDescription() const override
	{
		return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
			+ " syrup; ";
	}

private:
	SyrupType m_syrupType;
};

class ChocolateCrumbs : public CondimentDecorator
{
public:
	ChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
		: CondimentDecorator(move(beverage))
		, m_mass(mass)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 2.0 * m_mass;
	}

	std::string GetCondimentDescription() const override
	{
		return "Chocolate crumbs " + std::to_string(m_mass) + "g; ";
	}

private:
	unsigned m_mass;
};

class CoconutFlakes : public CondimentDecorator
{
public:
	CoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
		: CondimentDecorator(move(beverage))
		, m_mass(mass)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 1.0 * m_mass;
	}
	std::string GetCondimentDescription() const override
	{
		return "Coconut flakes " + std::to_string(m_mass) + "g; ";
	}

private:
	unsigned m_mass;
};

class Cream : public CondimentDecorator
{
public:
	Cream(IBeveragePtr&& beverage)
		: CondimentDecorator(move(beverage))
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 25;
	}
	std::string GetCondimentDescription() const override
	{
		return "Cream";
	}
};

class Chocolate : public CondimentDecorator
{
public:
	Chocolate(IBeveragePtr&& beverage, unsigned int count = 1)
		: CondimentDecorator(move(beverage))
	{
		if (count > 5)
		{
			throw std::out_of_range("Count of chocolates max = 5");
		}
		m_count = count;
	}

protected:
	double GetCondimentCost() const override
	{
		return m_count * 10;
	}
	std::string GetCondimentDescription() const override
	{
		return "Chocolate " + std::to_string(m_count) + "pieces; ";
	}

private:
	unsigned int m_count;
};

enum class LiquorType
{
	Nutty,
	Chocolate
};

class Liquor : public CondimentDecorator
{
public:
	Liquor(IBeveragePtr&& beverage, LiquorType liquorType)
		: CondimentDecorator(move(beverage))
		, m_type(liquorType)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 50;
	}
	std::string GetCondimentDescription() const override
	{
		return std::string(m_type == LiquorType::Chocolate ? "Chocolate" : "Nutty") + " liquor; ";
	}

private:
	LiquorType m_type;
};

} // namespace Condiment
