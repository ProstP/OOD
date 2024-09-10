#pragma once
#include "../Behaviors/Dance/Waltz.h"
#include "../Behaviors/Fly/FlyWithWings.h"
#include "../Behaviors/Quack/Quack.h"
#include "../Duck/Duck.h"

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(
			std::make_unique<Waltz>(),
			std::make_unique<FlyWithWings>(),
			std::make_unique<QuackBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};
