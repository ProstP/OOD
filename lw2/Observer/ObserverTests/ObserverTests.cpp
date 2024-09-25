#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/Observer/IObservable.h"
#include "../lib/Observer/IObserver.h"
#include <iostream>

using namespace Observer;

class TestObservable : public Observable<int>
{
public:
	int GetCounter()
	{
		return m_counter;
	}
	void ChangeCounter()
	{
		m_counter++;
		NotifyObservers();
	}
	~TestObservable() = default;

protected:
	int GetChangedData() const override
	{
		return m_counter;
	}
private:
	int m_counter = 0;
};

class TestObserver : public IObserver<int>
{
public:
	int GetCounter()
	{
		return m_counter;
	}
	void SetOvservable(IObservable<int>& o)
	{
		m_observable = &o;
		m_observable->RegisterObserver(*this);
	}
	~TestObserver() = default;

private:
	int m_counter = 0;
	IObservable<int>* m_observable;

	void Update(const int& data) override
	{
		m_counter = data;
		m_observable->RemoveObserver(*this);
	}
};

TEST_CASE("Observer deleting self from Observable list")
{
	WHEN("Deleting self from list in method Update")
	{
		TestObservable observable;
		TestObserver observer;
		observer.SetOvservable(observable);

		THEN("Without error")
		{
			CHECK_NOTHROW(observable.ChangeCounter());
			CHECK_NOTHROW(observable.ChangeCounter());
			CHECK(observable.GetCounter() == 2);
			CHECK(observer.GetCounter() == 1);
		}
	}
}
