#pragma once
#include "../Behaviors/Dance/NoDance.h"
#include "../Behaviors/Fly/FlyNoWay.h"
#include "../Behaviors/Quack/MuteQuack.h"
#include "../Duck/Duck.h"

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(
			std::make_unique<NoDance>(),
			std::make_unique<FlyNoWay>(),
			std::make_unique<MuteQuack>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};
