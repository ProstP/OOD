#pragma once
#include "IObservable.h"

namespace Observer
{

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

private:
	std::set<ObserverType*> m_observers;
};

} // namespace Obversable
