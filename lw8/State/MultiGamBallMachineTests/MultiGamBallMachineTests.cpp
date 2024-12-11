#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/MultiGamBallMachine/MultiGamBallMachine.h"
#include <iostream>

using namespace MultiGumBallMachine;

TEST_CASE("Naive machine insert money")
{
	WHEN("Sold out")
	{
		NaiveMultiGamBullMachine machine(0);
		std::string state = machine.ToString();

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == state);
		}
	}
	WHEN("No quarter")
	{
		NaiveMultiGamBullMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs, 1 quarter\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("State be has quarter and 1 quarter")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Has quarter")
	{
		NaiveMultiGamBullMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs, 2 quarters\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("State be has quarter and 2 quarters")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Quarter count is 5")
	{
		NaiveMultiGamBullMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs, 5 quarters\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("After 5 don't get quarter")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
		}
	}
}

TEST_CASE("Naive machine eject quarter")
{
	WHEN("Quarter count is 0")
	{
		NaiveMultiGamBullMachine machine(5);
		std::string state = machine.ToString();

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == state);
		}
	}
	WHEN("Quarter count is 1")
	{
		NaiveMultiGamBullMachine machine(5);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 5 gumballs, 1 quarter\n";
		expectedBefore += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == expectedAfter);
		}
	}
	WHEN("Quarter count > 1")
	{
		NaiveMultiGamBullMachine machine(5);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 5 gumballs, 5 quarters\n";
		expectedBefore += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == expectedAfter);
		}
	}
}

TEST_CASE("Naive machine turn of crank")
{
	WHEN("Quarter count = 0")
	{
		NaiveMultiGamBullMachine machine(5);
		std::string state = machine.ToString();

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == state);
		}
	}
	WHEN("Quarter count > 1, turn while quarter count isn't 0")
	{
		NaiveMultiGamBullMachine machine(5);
		std::string expectedBefore2 = "\n";
		expectedBefore2 += "Mighty Gumball, Inc.\n";
		expectedBefore2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore2 += "Inventory: 5 gumballs, 2 quarters\n";
		expectedBefore2 += "Machine is waiting for turn of crank\n";

		std::string expectedBefore1 = "\n";
		expectedBefore1 += "Mighty Gumball, Inc.\n";
		expectedBefore1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore1 += "Inventory: 4 gumballs, 1 quarter\n";
		expectedBefore1 += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 3 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Gamball is less, quarter too")
		{

			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore2);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedBefore1);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedAfter);
		}
	}

	WHEN("Quarter and gamball count is equal")
	{
		NaiveMultiGamBullMachine machine(2);
		std::string expectedBefore2 = "\n";
		expectedBefore2 += "Mighty Gumball, Inc.\n";
		expectedBefore2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore2 += "Inventory: 2 gumballs, 2 quarters\n";
		expectedBefore2 += "Machine is waiting for turn of crank\n";

		std::string expectedBefore1 = "\n";
		expectedBefore1 += "Mighty Gumball, Inc.\n";
		expectedBefore1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore1 += "Inventory: 1 gumball, 1 quarter\n";
		expectedBefore1 += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 0 gumballs, 0 quarters\n";
		expectedAfter += "Machine is sold out\n";

		THEN("Gamball is sold out")
		{

			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore2);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedBefore1);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedAfter);
		}
	}

	WHEN("Quarter count > gamball count")
	{
		NaiveMultiGamBullMachine machine(2);
		std::string expectedBefore2 = "\n";
		expectedBefore2 += "Mighty Gumball, Inc.\n";
		expectedBefore2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore2 += "Inventory: 2 gumballs, 4 quarters\n";
		expectedBefore2 += "Machine is waiting for turn of crank\n";

		std::string expectedBefore1 = "\n";
		expectedBefore1 += "Mighty Gumball, Inc.\n";
		expectedBefore1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore1 += "Inventory: 1 gumball, 3 quarters\n";
		expectedBefore1 += "Machine is waiting for turn of crank\n";

		std::string expectedAfter1 = "\n";
		expectedAfter1 += "Mighty Gumball, Inc.\n";
		expectedAfter1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter1 += "Inventory: 0 gumballs, 2 quarters\n";
		expectedAfter1 += "Machine is sold out\n";

		std::string expectedAfter2 = "\n";
		expectedAfter2 += "Mighty Gumball, Inc.\n";
		expectedAfter2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter2 += "Inventory: 0 gumballs, 0 quarters\n";
		expectedAfter2 += "Machine is sold out\n";

		THEN("Gamball is sold out")
		{

			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore2);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedBefore1);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedAfter1);
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == expectedAfter2);
		}
	}
}

TEST_CASE("Machine insert money")
{
	WHEN("Sold out")
	{
		MultiGumballMachine machine(0);
		std::string state = machine.ToString();

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == state);
		}
	}
	WHEN("No quarter")
	{
		MultiGumballMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs, 1 quarter\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("State be has quarter and 1 quarter")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Has quarter")
	{
		MultiGumballMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs, 2 quarters\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("State be has quarter and 2 quarters")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
		}
	}
	WHEN("Quarter count is 5")
	{
		MultiGumballMachine machine(5);

		std::string expected = "\n";
		expected += "Mighty Gumball, Inc.\n";
		expected += "C++-enabled Standing Gumball Model #2024\n";
		expected += "Inventory: 5 gumballs, 5 quarters\n";
		expected += "Machine is waiting for turn of crank\n";

		THEN("After 5 don't get quarter")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expected);
		}
	}
}

TEST_CASE("Machine eject quarter")
{
	WHEN("Quarter count is 0")
	{
		MultiGumballMachine machine(5);
		std::string state = machine.ToString();

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == state);
		}
	}
	WHEN("Quarter count is 1")
	{
		MultiGumballMachine machine(5);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 5 gumballs, 1 quarter\n";
		expectedBefore += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == expectedAfter);
		}
	}
	WHEN("Quarter count > 1")
	{
		MultiGumballMachine machine(5);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 5 gumballs, 5 quarters\n";
		expectedBefore += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == expectedAfter);
		}
	}
}

TEST_CASE("Turn of crank")
{
	WHEN("Quarter count = 0")
	{
		MultiGumballMachine machine(5);
		std::string state = machine.ToString();

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == state);
		}
	}
	WHEN("Quarter count > 1, turn while quarter count isn't 0")
	{
		MultiGumballMachine machine(5);
		std::string expectedBefore2 = "\n";
		expectedBefore2 += "Mighty Gumball, Inc.\n";
		expectedBefore2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore2 += "Inventory: 5 gumballs, 2 quarters\n";
		expectedBefore2 += "Machine is waiting for turn of crank\n";

		std::string expectedBefore1 = "\n";
		expectedBefore1 += "Mighty Gumball, Inc.\n";
		expectedBefore1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore1 += "Inventory: 4 gumballs, 1 quarter\n";
		expectedBefore1 += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 3 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Gamball is less, quarter too")
		{

			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore2);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedBefore1);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedAfter);
		}
	}

	WHEN("Quarter and gamball count is equal")
	{
		MultiGumballMachine machine(2);
		std::string expectedBefore2 = "\n";
		expectedBefore2 += "Mighty Gumball, Inc.\n";
		expectedBefore2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore2 += "Inventory: 2 gumballs, 2 quarters\n";
		expectedBefore2 += "Machine is waiting for turn of crank\n";

		std::string expectedBefore1 = "\n";
		expectedBefore1 += "Mighty Gumball, Inc.\n";
		expectedBefore1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore1 += "Inventory: 1 gumball, 1 quarter\n";
		expectedBefore1 += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 0 gumballs, 0 quarters\n";
		expectedAfter += "Machine is sold out\n";

		THEN("Gamball is sold out")
		{

			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore2);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedBefore1);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedAfter);
		}
	}

	WHEN("Quarter count > gamball count")
	{
		MultiGumballMachine machine(2);
		std::string expectedBefore2 = "\n";
		expectedBefore2 += "Mighty Gumball, Inc.\n";
		expectedBefore2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore2 += "Inventory: 2 gumballs, 4 quarters\n";
		expectedBefore2 += "Machine is waiting for turn of crank\n";

		std::string expectedBefore1 = "\n";
		expectedBefore1 += "Mighty Gumball, Inc.\n";
		expectedBefore1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore1 += "Inventory: 1 gumball, 3 quarters\n";
		expectedBefore1 += "Machine is waiting for turn of crank\n";

		std::string expectedAfter1 = "\n";
		expectedAfter1 += "Mighty Gumball, Inc.\n";
		expectedAfter1 += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter1 += "Inventory: 0 gumballs, 2 quarters\n";
		expectedAfter1 += "Machine is sold out\n";

		std::string expectedAfter2 = "\n";
		expectedAfter2 += "Mighty Gumball, Inc.\n";
		expectedAfter2 += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter2 += "Inventory: 0 gumballs, 0 quarters\n";
		expectedAfter2 += "Machine is sold out\n";

		THEN("Gamball is sold out")
		{

			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore2);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedBefore1);
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedAfter1);
			CHECK_NOTHROW(machine.EjectQuarter());
			CHECK(machine.ToString() == expectedAfter2);
		}
	}
}

TEST_CASE("Fill automata")
{
	WHEN("Sold out state with no quarter")
	{
		MultiGumballMachine machine(0);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 0 gumballs, 0 quarters\n";
		expectedBefore += "Machine is sold out\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Gumball count is greated")
		{
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.Fill(5));
			CHECK(machine.ToString() == expectedAfter);
		}
	}
	WHEN("Sold out state with quarter")
	{
		MultiGumballMachine machine(1);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 0 gumballs, 1 quarter\n";
		expectedBefore += "Machine is sold out\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 1 quarter\n";
		expectedAfter += "Machine is waiting for turn of crank\n";

		THEN("Gumball count is greated")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK_NOTHROW(machine.TurnCrank());
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.Fill(5));
			CHECK(machine.ToString() == expectedAfter);
		}
	}
	WHEN("No quarter state")
	{
		MultiGumballMachine machine(1);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 1 gumball, 0 quarters\n";
		expectedBefore += "Machine is waiting for quarter\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 0 quarters\n";
		expectedAfter += "Machine is waiting for quarter\n";

		THEN("Success added")
		{
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.Fill(4));
			CHECK(machine.ToString() == expectedAfter);
		}
	}
	WHEN("Has quarter")
	{
		MultiGumballMachine machine(1);

		std::string expectedBefore = "\n";
		expectedBefore += "Mighty Gumball, Inc.\n";
		expectedBefore += "C++-enabled Standing Gumball Model #2024\n";
		expectedBefore += "Inventory: 1 gumball, 1 quarter\n";
		expectedBefore += "Machine is waiting for turn of crank\n";

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 5 gumballs, 1 quarter\n";
		expectedAfter += "Machine is waiting for turn of crank\n";

		THEN("Success added")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == expectedBefore);
			CHECK_NOTHROW(machine.Fill(4));
			CHECK(machine.ToString() == expectedAfter);
		}
	}
}

class TestMachine : public IMultiGumballMachine
{
public:
	void AddGumballs(unsigned gumballCount)
	{
		m_count += gumballCount;
	}
	void ReleaseBall()
	{
		if (m_count != 0)
		{
			--m_count;
		}
	}
	unsigned GetBallCount() const
	{
		return m_count;
	}

	void EjectQuarters()
	{
		m_quarter = 0;
	}
	void UseQuarter()
	{
		if (m_quarter != 0)
		{
			--m_quarter;
		}
	}
	void AddQuarter()
	{
		++m_quarter;
	}
	unsigned GetQuarterCount() const
	{
		return m_quarter;
	}

	void SetSoldOutState()
	{
		m_state = "sold out";
	}
	void SetNoQuarterState()
	{
		m_state = "no quarter";
	}
	void SetSoldState()
	{
		m_state = "sold";
	}
	void SetHasQuarterState()
	{
		m_state = "has quarter";
	}

	unsigned m_count = 0;
	unsigned m_quarter = 0;
	std::string m_state;
};

TEST_CASE("States")
{
	TestMachine machine;

	WHEN("Sold out with 0 quarter")
	{
		SoldOutState state(machine);

		THEN("Gumball count is greate")
		{
			CHECK(machine.m_count == 0);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "");
			CHECK_NOTHROW(state.AddGumballs(5));
			CHECK(machine.m_count == 5);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "no quarter");
		}
	}
	WHEN("Sold out with some quarter")
	{
		SoldOutState state(machine);
		machine.m_quarter = 4;

		THEN("Gumball count is greate")
		{
			CHECK(machine.m_count == 0);
			CHECK(machine.m_quarter == 4);
			CHECK(machine.m_state == "");
			CHECK_NOTHROW(state.AddGumballs(5));
			CHECK(machine.m_count == 5);
			CHECK(machine.m_quarter == 4);
			CHECK(machine.m_state == "has quarter");
		}
	}
	WHEN("No quarter")
	{
		NoQuarterState state(machine);

		THEN("Gumball count is greate")
		{
			CHECK(machine.m_count == 0);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "");
			CHECK_NOTHROW(state.AddGumballs(5));
			CHECK(machine.m_count == 5);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "");
		}
	}
	WHEN("Has quarter")
	{
		HasQuarterState state(machine);

		THEN("Gumball count is greate")
		{
			CHECK(machine.m_count == 0);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "");
			CHECK_NOTHROW(state.AddGumballs(5));
			CHECK(machine.m_count == 5);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "");
		}
	}
	WHEN("Sold")
	{
		SoldState state(machine);

		THEN("Gumball count is greate")
		{
			CHECK(machine.m_count == 0);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "");
			CHECK_NOTHROW(state.AddGumballs(5));
			CHECK(machine.m_count == 0);
			CHECK(machine.m_quarter == 0);
			CHECK(machine.m_state == "");
		}
	}
}
