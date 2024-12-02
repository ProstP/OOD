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
		expectedAfter += "Inventory: 5 gumballs, 4 quarters\n";
		expectedAfter += "Machine is waiting for turn of crank\n";

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

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 0 gumballs, 2 quarters\n";
		expectedAfter += "Machine is sold out\n";

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
			CHECK(machine.ToString() == expectedAfter);
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
		expectedAfter += "Inventory: 5 gumballs, 4 quarters\n";
		expectedAfter += "Machine is waiting for turn of crank\n";

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

		std::string expectedAfter = "\n";
		expectedAfter += "Mighty Gumball, Inc.\n";
		expectedAfter += "C++-enabled Standing Gumball Model #2024\n";
		expectedAfter += "Inventory: 0 gumballs, 2 quarters\n";
		expectedAfter += "Machine is sold out\n";

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
			CHECK(machine.ToString() == expectedAfter);
		}
	}
}
