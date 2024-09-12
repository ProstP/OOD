#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Ducks/lib/Behaviors/IDanceBehavior.h"
#include "../Ducks/lib/SamplesDuck/MallardDuck.h"
#include <iostream>

class TestDance : public IDanceBehavior
{
public:
	void Dance() override
	{
		m_Counter++;
	}

	int GetCounter()
	{
		return m_Counter;
	}

private:
	int m_Counter = 0;
};

TEST_CASE("Dance menthod")
{
	WHEN("Set test dance to duck and dance")
	{
		std::unique_ptr<TestDance> danceBehavior{ std::make_unique<TestDance>() };
		TestDance* ptr = danceBehavior.get();

		MallardDuck duck;
		duck.SetDanceBehavior(std::move(danceBehavior));

		THEN("Counter will be increase")
		{
			//Как написать тест который юы доказывал утка бует танцевать прик каждом вызове и не оставносится
			duck.Dance();

			CHECK(ptr->GetCounter() == 1);
			duck.Dance();

			CHECK(ptr->GetCounter() == 2);
		}
	}
}
