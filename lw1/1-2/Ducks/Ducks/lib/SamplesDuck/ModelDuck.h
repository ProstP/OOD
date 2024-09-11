#pragma once
#include "../Behaviors/Dance/NoDance.h"
#include "../Behaviors/Fly/FlyNoWay.h"
#include "../Behaviors/Quack/Quack.h"
#include "../Duck/Duck.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(
			std::make_unique<NoDance>(),
			std::make_unique<FlyNoWay>(),
			std::make_unique<QuackBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};
