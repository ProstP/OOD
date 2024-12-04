#pragma once
#include <format>
#include <iostream>

namespace MultiGumBallMachine
{

class IState
{
public:
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual std::string ToString() const = 0;

	virtual ~IState() = default;
};

class IMultiGumballMachine
{
public:
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;

	virtual void ReleaseQuarter() = 0;
	virtual void AddQuarter() = 0;
	virtual unsigned GetQuarterCount() const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IMultiGumballMachine() = default;
};

class SoldState : public IState
{
public:
	SoldState(IMultiGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		m_gumballMachine.ReleaseQuarter();//Разные методы

		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			if (m_gumballMachine.GetQuarterCount() == 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetHasQuarterState();
			}
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IMultiGumballMachine& m_gumballMachine;
};

class SoldOutState : public IState
{
public:
	SoldOutState(IMultiGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		std::cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}

private:
	IMultiGumballMachine& m_gumballMachine;
};

class HasQuarterState : public IState
{
public:
	HasQuarterState(IMultiGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		if (m_gumballMachine.GetQuarterCount() >= 5)
		{
			std::cout << "You can't insert another quarter\n";
		}
		else
		{
			std::cout << "You insert quarter\n";
			m_gumballMachine.AddQuarter();
		}
	}
	void EjectQuarter() override
	{
		if (m_gumballMachine.GetQuarterCount() > 0)
		{
			std::cout << "Quarter returned\n";
			m_gumballMachine.ReleaseQuarter();

			if (m_gumballMachine.GetQuarterCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();

				return;
			}
		}

		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

private:
	IMultiGumballMachine& m_gumballMachine;
};

class NoQuarterState : public IState
{
public:
	NoQuarterState(IMultiGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.AddQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}

private:
	IMultiGumballMachine& m_gumballMachine;
};

class MultiGumballMachine : private IMultiGumballMachine
{
public:
	MultiGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	std::string ToString() const
	{
		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2024
Inventory: {} gumball{}, {} quarter{}
Machine is {}
)",
			m_count, m_count != 1 ? "s" : "", m_quarterCount, m_quarterCount != 1 ? "s" : "", m_state->ToString());
	}

private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}
	void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	unsigned GetQuarterCount() const override
	{
		return m_quarterCount;
	}
	void AddQuarter() override
	{
		if (m_quarterCount < 5)
		{
			++m_quarterCount;
		}
	}
	void ReleaseQuarter() override
	{
		if (m_quarterCount != 0)
		{
			--m_quarterCount;
		}
	}
	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

private:
	unsigned m_count = 0;
	unsigned m_quarterCount = 0;
	SoldState m_soldState;
	SoldOutState m_soldOutState;
	NoQuarterState m_noQuarterState;
	HasQuarterState m_hasQuarterState;
	IState* m_state;
};

class NaiveMultiGamBullMachine
{
public:
	NaiveMultiGamBullMachine(unsigned count)
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
			if (m_quarterCount == 0)
			{
				m_state = State::NoQuarter;
				break;
			}
			std::cout << "Quarter returned\n";
			--m_quarterCount;

			if (m_quarterCount == 0)
			{
				m_state = State::NoQuarter;
			}
			else
			{
				m_state = State::HasQuarter;
			}

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
			if (m_count == 0 || m_quarterCount == 0)
			{
				break;
			}
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
			--m_quarterCount;

			if (m_count == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				if (m_quarterCount == 0)
				{
					m_state = State::NoQuarter;
				}
				else
				{
					m_state = State::HasQuarter;
				}
			}
			break;
		case State::HasQuarter:
		case State::NoQuarter:
			std::cout << "No gumball dispensed\n";
			break;
		}
	}
};

} // namespace MultiGumBallMachine
