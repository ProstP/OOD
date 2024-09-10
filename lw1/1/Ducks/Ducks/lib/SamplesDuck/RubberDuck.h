#pragma once
#include "../Behaviors/Dance/NoDance.h"
#include "../Behaviors/Fly/FlyNoWay.h"
#include "../Behaviors/Quack/Squeak.h"
#include "../Duck/Duck.h"

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(
			std::make_unique<NoDance>(),
			std::make_unique<FlyNoWay>(),
			std::make_unique<Squeak>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};
