#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/Observer/Observer.h"
#include <iostream>

class DuoObservable : public Observer::Observable<int>
{
public:
	int GetChangedData() const override
	{
		return 0;
	}

private:
};

class DuoObserver : public Observer::IObserver<int>
{
public:
	void SetFirst(DuoObservable& first)
	{
		m_first = &first;
		m_first->RegisterObserver(*this);
	}
	void SetSecond(DuoObservable& second)
	{
		m_second = &second;
		m_second->RegisterObserver(*this);
	}
	int GetNum()
	{
		return m_num;
	}

private:
	DuoObservable* m_first;
	DuoObservable* m_second;
	int m_num = 0;

	void Update(Observer::IObservable<int>& subj) override
	{
		if (&subj == m_first)
		{
			m_num = 1;
		}
		if (&subj == m_second)
		{
			m_num = 2;
		}
	}
};

TEST_CASE("Test duo observable")
{
	WHEN("Both observable update data")
	{
		DuoObservable first;
		DuoObservable second;
		DuoObserver observer;
		observer.SetFirst(first);
		observer.SetSecond(second);

		THEN("If update first num of obsever == 1, second - 2")
		{
			CHECK(observer.GetNum() == 0);
			CHECK_NOTHROW(first.NotifyObservers());
			CHECK(observer.GetNum() == 1);
			CHECK_NOTHROW(second.NotifyObservers());
			CHECK(observer.GetNum() == 2);
		}
	}
}
