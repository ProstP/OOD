#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/MultiGamBallMachine/MultiGamBallMachine.h"
#include <iostream>

using namespace MultiGamBallMachine;

TEST_CASE("Naive machine insert money")
{
	WHEN("Sold out")
	{
		NaiveMultiGamBallMachine machine(0);
		std::string state = machine.ToString();

		THEN("Nothing")
		{
			CHECK_NOTHROW(machine.InsertQuarter());
			CHECK(machine.ToString() == state);
		}
	}
	WHEN("No quarter")
	{
		NaiveMultiGamBallMachine machine(5);

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
		NaiveMultiGamBallMachine machine(5);
		std::string state = machine.ToString();

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
		NaiveMultiGamBallMachine machine(5);
		std::string state = machine.ToString();

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
