#pragma once
#include "../Behaviors/Dance/Minuet.h"
#include "../Behaviors/Fly/FlyWithWings.h"
#include "../Behaviors/Quack/Quack.h"
#include "../Duck/Duck.h"

class ReheadDuck : public Duck
{
public:
	ReheadDuck()
		: Duck(
			std::make_unique<Minuet>(),
			std::make_unique<FlyWithWings>(),
			std::make_unique<QuackBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};
