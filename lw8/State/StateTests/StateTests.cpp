#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/GamBallMachine/GumBallMachine.h"
#include <iostream>

using namespace GamBallMachine;

class TestMachine : public IGumballMachine
{
public:
	void ReleaseBall() override
	{
		if (m_ballCount != 0)
		{
			--m_ballCount;
		}
	}
	unsigned GetBallCount() const override
	{
		return m_ballCount;
	}

	void SetSoldOutState() override
	{
		m_state = States::SoldOut;
	}
	void SetNoQuarterState() override
	{
		m_state = States::NoQuarter;
	}
	void SetSoldState() override
	{
		m_state = States::Sold;
	}
	void SetHasQuarterState() override
	{
		m_state = States::HasQuarter;
	}

	enum class States
	{
		SoldOut,
		NoQuarter,
		Sold,
		HasQuarter
	};

	unsigned m_ballCount = 0;
	States m_state = States::SoldOut;
};

TEST_CASE("SoldState")
{
	TestMachine machine;
	machine.m_ballCount = 5;
	unsigned oldCount = machine.m_ballCount;
	TestMachine::States oldState = machine.m_state;
	SoldState state(machine);

	WHEN("Insert quarter")
	{
		state.InsertQuarter();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Eject quarter")
	{
		state.EjectQuarter();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Turn crank")
	{
		state.TurnCrank();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Dispanse")
	{
		state.Dispense();

		THEN("Decrease count and set no quarter state")
		{
			CHECK(machine.m_state == TestMachine::States::NoQuarter);
			CHECK(machine.m_ballCount == oldCount - 1);
		}
	}
	WHEN("Dispanse when count 1")
	{
		machine.m_ballCount = 1;

		state.Dispense();

		THEN("Count = 0 and set no sold out state")
		{
			CHECK(machine.m_state == TestMachine::States::SoldOut);
			CHECK(machine.m_ballCount == 0);
		}
	}
	WHEN("Dispanse when count 0")
	{
		machine.m_ballCount = 0;

		state.Dispense();

		THEN("Count = 0 and set no sold out state")
		{
			CHECK(machine.m_state == TestMachine::States::SoldOut);
			CHECK(machine.m_ballCount == 0);
		}
	}
}

TEST_CASE("SoldOut")
{
	TestMachine machine;
	machine.m_ballCount = 5;
	unsigned oldCount = machine.m_ballCount;
	TestMachine::States oldState = machine.m_state;
	SoldOutState state(machine);

	WHEN("Insert quarter")
	{
		state.InsertQuarter();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Eject quarter")
	{
		state.EjectQuarter();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Turn crank")
	{
		state.TurnCrank();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Dispanse")
	{
		state.Dispense();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
}

TEST_CASE("Has quarter")
{
	TestMachine machine;
	machine.m_ballCount = 5;
	unsigned oldCount = machine.m_ballCount;
	TestMachine::States oldState = machine.m_state;
	HasQuarterState state(machine);

	WHEN("Insert quarter")
	{
		state.InsertQuarter();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Eject quarter")
	{
		state.EjectQuarter();

		THEN("State is no quarter")
		{
			CHECK(machine.m_state == TestMachine::States::NoQuarter);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Turn crank")
	{
		state.TurnCrank();

		THEN("State is sold")
		{
			CHECK(machine.m_state == TestMachine::States::Sold);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Dispanse")
	{
		state.Dispense();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
}

TEST_CASE("No quarter")
{
	TestMachine machine;
	machine.m_ballCount = 5;
	unsigned oldCount = machine.m_ballCount;
	TestMachine::States oldState = machine.m_state;
	NoQuarterState state(machine);

	WHEN("Insert quarter")
	{
		state.InsertQuarter();

		THEN("State is has quarter")
		{
			CHECK(machine.m_state == TestMachine::States::HasQuarter);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Eject quarter")
	{
		state.EjectQuarter();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Turn crank")
	{
		state.TurnCrank();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
	WHEN("Dispanse")
	{
		state.Dispense();

		THEN("Nothing")
		{
			CHECK(machine.m_state == oldState);
			CHECK(machine.m_ballCount == oldCount);
		}
	}
}

TEST_CASE("Initial machine")
{
	WHEN("Ball count = 0")
	{
		GumballMachine machine(0);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 0 gumballs\n";
		expected += "Machine is sold out\n";

		THEN("BAll count is 0, state is sold out")
		{
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Ball count = 1")
	{
		GumballMachine machine(1);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 1 gumball\n";
		expected += "Machine is waiting for quarter\n";

		THEN("BAll count is 1, state is no quarter")
		{
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Ball count > 1")
	{
		GumballMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs\n";
		expected += "Machine is waiting for quarter\n";

		THEN("BAll count is 5, state is no quarter")
		{
			CHECK(machine.ToString() == expected);
		}
	}
}

TEST_CASE("Machine in sold out state")
{
	GumballMachine machine(0);
	const std::string state = machine.ToString();

	WHEN("Insert quarter")
	{
		machine.InsertQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Eject quarter")
	{
		machine.EjectQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Turn crank")
	{
		machine.TurnCrank();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}
}

TEST_CASE("Machine in no quarter state")
{
	GumballMachine machine(5);
	const std::string state = machine.ToString();

	WHEN("Insert quarter")
	{
		machine.InsertQuarter();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("State is has quarter")
		{
			CHECK(expected == machine.ToString());
		}
	}

	WHEN("Eject quarter")
	{
		machine.EjectQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Turn crank")
	{
		machine.TurnCrank();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}
}

TEST_CASE("Machine in has quarter state")
{
	GumballMachine machine(5);
	machine.InsertQuarter();
	const std::string state = machine.ToString();

	WHEN("Insert quarter")
	{
		machine.InsertQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Eject quarter")
	{
		machine.EjectQuarter();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs\n";
		expected += "Machine is waiting for quarter\n";

		THEN("State is no quarty")
		{
			CHECK(expected == machine.ToString());
		}
	}

	WHEN("Turn crank balls > 1")
	{
		machine.TurnCrank();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 4 gumballs\n";
		expected += "Machine is waiting for quarter\n";

		THEN("State will be no quarter, ball count decrease")
		{
			CHECK(expected == machine.ToString());
		}
	}

	WHEN("Turn crank balls = 1")
	{
		GumballMachine machineWithOneBall(1);
		machineWithOneBall.InsertQuarter();
		machineWithOneBall.TurnCrank();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 0 gumballs\n";
		expected += "Machine is sold out\n";

		THEN("State will be sold out, ball count = 0")
		{
			CHECK(expected == machineWithOneBall.ToString());
		}
	}
}

TEST_CASE("Initial naive machine")
{
	WHEN("Ball count = 0")
	{
		NaiveGamBallMachine machine(0);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 0 gumballs\n";
		expected += "Machine is sold out\n";

		THEN("BAll count is 0, state is sold out")
		{
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Ball count = 1")
	{
		NaiveGamBallMachine machine(1);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 1 gumball\n";
		expected += "Machine is waiting for quarter\n";

		THEN("BAll count is 1, state is no quarter")
		{
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Ball count > 1")
	{
		NaiveGamBallMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs\n";
		expected += "Machine is waiting for quarter\n";

		THEN("BAll count is 5, state is no quarter")
		{
			CHECK(machine.ToString() == expected);
		}
	}
}

TEST_CASE("Naive machine in sold out state")
{
	NaiveGamBallMachine machine(0);
	const std::string state = machine.ToString();

	WHEN("Insert quarter")
	{
		machine.InsertQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Eject quarter")
	{
		machine.EjectQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Turn crank")
	{
		machine.TurnCrank();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}
}

TEST_CASE("Naive machine in no quarter state")
{
	NaiveGamBallMachine machine(5);
	const std::string state = machine.ToString();

	WHEN("Insert quarter")
	{
		machine.InsertQuarter();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("State is has quarter")
		{
			CHECK(expected == machine.ToString());
		}
	}

	WHEN("Eject quarter")
	{
		machine.EjectQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Turn crank")
	{
		machine.TurnCrank();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}
}

TEST_CASE("Naive machine in has quarter state")
{
	NaiveGamBallMachine machine(5);
	machine.InsertQuarter();
	const std::string state = machine.ToString();

	WHEN("Insert quarter")
	{
		machine.InsertQuarter();

		THEN("Nothing")
		{
			CHECK(state == machine.ToString());
		}
	}

	WHEN("Eject quarter")
	{
		machine.EjectQuarter();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs\n";
		expected += "Machine is waiting for quarter\n";

		THEN("State is no quarty")
		{
			CHECK(expected == machine.ToString());
		}
	}

	WHEN("Turn crank balls > 1")
	{
		machine.TurnCrank();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 4 gumballs\n";
		expected += "Machine is waiting for quarter\n";

		THEN("State will be no quarter, ball count decrease")
		{
			CHECK(expected == machine.ToString());
		}
	}

	WHEN("Turn crank balls = 1")
	{
		NaiveGamBallMachine machineWithOneBall(1);
		machineWithOneBall.InsertQuarter();
		machineWithOneBall.TurnCrank();

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 0 gumballs\n";
		expected += "Machine is sold out\n";

		THEN("State will be sold out, ball count = 0")
		{
			CHECK(expected == machineWithOneBall.ToString());
		}
	}
}
