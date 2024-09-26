#pragma once
#include <iostream>
#include <set>

namespace Observer
{
template <typename T>
class IObserver;

template <typename T>
class IObservable
{
public:
	virtual void RegisterObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual T GetChangedData() const = 0;

	virtual ~IObservable() = default;
};

template <typename T>
class Observable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer) override
	{
		m_observers.insert(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = m_observers;
		for (auto* observer : observers)
		{
			observer->Update(*this);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
	}

	virtual T GetChangedData() const = 0;

private:
	std::set<ObserverType*> m_observers;
};

template <typename T>
class IObserver
{
public:
	virtual void Update(IObservable<T>& subj) = 0;
	virtual ~IObserver() = default;
};

} // namespace Observer
