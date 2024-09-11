#pragma once
#include "../Behaviors/Dance/Waltz.h"
#include "../Behaviors/Fly/FlyWithWings.h"
#include "../Behaviors/Quack/Quack.h"
#include "../Duck/Duck.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(
			std::make_unique<Waltz>(),
			std::make_unique<FlyWithWings>(),
			std::make_unique<QuackBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};
