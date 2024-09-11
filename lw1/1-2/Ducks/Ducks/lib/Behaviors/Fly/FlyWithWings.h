#pragma once
#include "../IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_flyingCount++;
		std::cout << "I'm flying with wings!! It's my " << m_flyingCount << " departure." << std::endl;
	}

private:
	int m_flyingCount = 0;
};
