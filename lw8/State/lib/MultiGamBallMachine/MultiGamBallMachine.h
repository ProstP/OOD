#pragma once
#include <format>
#include <iostream>

namespace MultiGamBallMachine
{

class NaiveMultiGamBallMachine
{
public:
	NaiveMultiGamBallMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut){};

	void EjectQuarter()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			break;
		case State::NoQuarter:
			std::cout << "You haven't inserted a quarter\n";
			break;
		case State::HasQuarter:
			std::cout << "Quarter returned\n";
			m_state = State::NoQuarter;
			break;
		case State::Sold:
			std::cout << "Sorry you already turned the crank\n";
			break;
		}
	}
	void InsertQuarter()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			std::cout << "You inserted a quarter\n";
			++m_quarterCount;
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_quarterCount < 5)
			{
				std::cout << "You inserted a quarter\n";
				++m_quarterCount;
			}
			else
			{
				std::cout << "You can't insert another quarter\n";
			}
			break;
		case State::Sold:
			std::cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}
	void TurnCrank()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			std::cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			std::cout << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			std::cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	std::string ToString()
	{
		std::string stateStr;
		switch (m_state)
		{
		case State::SoldOut:
			stateStr = "sold out";
			break;
		case State::NoQuarter:
			stateStr = "waiting for quarter";
			break;
		case State::HasQuarter:
			stateStr = "waiting for turn of crank";
			break;
		case State::Sold:
			stateStr = "delivering a gumball";
			break;
		}

		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2024
Inventory: {} gumball{}, {} quarter{}
Machine is {}
)",
			m_count, m_count != 1 ? "s" : "", m_quarterCount, m_quarterCount != 1 ? "s" : "", stateStr);
	}

private:
	enum class State
	{
		SoldOut,
		NoQuarter,
		HasQuarter,
		Sold
	};
	unsigned m_count;
	unsigned m_quarterCount = 0;
	State m_state;

	void Dispense()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "No gumball dispensed\n";
			break;
		case State::Sold:
			if (m_count == 0)
			{
				break;
			}
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;

			if (m_count == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		case State::HasQuarter:
		case State::NoQuarter:
			std::cout << "No gumball dispensed\n";
			break;
		}
	}
};

} // namespace MultiGamBallMachine
