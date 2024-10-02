#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/Observer/Observer.h"
#include <iostream>

using namespace Observer;

class TestObservable : public Observable
{
public:
	TestObservable()
	{
		AddType("first");
		AddType("second");
	}

	void NotifyError()
	{
		NotifyObservers("third");
	}

	void SetFirst()
	{
		m_first = 1;
		NotifyObservers("first");
	}
	void SetSecond()
	{
		m_first = 0;
		m_second = 2;
		NotifyObservers("second");
	}

	int GetFirst()
	{
		return m_first;
	}
	int GetSecond()
	{
		return m_second;
	}

private:
	int m_first = -1;
	int m_second = -1;
};

class FirstObserver : public IObserver
{
public:
	void SetObservable(TestObservable& observable)
	{
		m_ptr = &observable;
		m_ptr->RegisterObserver("first", *this);
	}
	int GetFirst() const
	{
		return m_first;
	}

private:
	TestObservable* m_ptr;
	int m_first = 0;
	void Update(IObservable& subj) override
	{
		if (m_ptr == &subj)
		{
			m_first = m_ptr->GetFirst();
		}
	}
};

class SecondObserver : public IObserver
{
public:
	void SetObservable(TestObservable& observable)
	{
		m_ptr = &observable;
		m_ptr->RegisterObserver("second", *this);
	}
	int GetSecond() const
	{
		return m_second;
	}

private:
	TestObservable* m_ptr;
	int m_second = 0;
	void Update(IObservable& subj) override
	{
		if (m_ptr == &subj)
		{
			m_second = m_ptr->GetSecond();
		}
	}
};

TEST_CASE("Hotify different actions")
{
	TestObservable observable;

	WHEN("Unknown type of action")
	{
		THEN("Throw ecxeption")
		{
			CHECK_THROWS_AS(observable.NotifyError(), std::invalid_argument);
		}
	}

	WHEN("Different actions")
	{
		FirstObserver first;
		SecondObserver second;

		first.SetObservable(observable);
		second.SetObservable(observable);

		THEN("Defferent values")
		{
			CHECK(first.GetFirst() == 0);
			CHECK(second.GetSecond() == 0);
			CHECK(observable.GetFirst() == -1);
			CHECK(observable.GetSecond() == -1);
			observable.SetFirst();
			CHECK(first.GetFirst() == 1);
			CHECK(second.GetSecond() == 0);
			CHECK(observable.GetFirst() == 1);
			CHECK(observable.GetSecond() == -1);
			observable.SetSecond();
			CHECK(first.GetFirst() == 1);
			CHECK(second.GetSecond() == 2);
			CHECK(observable.GetFirst() == 0);
			CHECK(observable.GetSecond() == 2);
		}
	}
}
