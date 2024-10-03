#pragma once
#include <iostream>
#include <map>
#include <set>

namespace Observer
{

class IObserver;

// T шаблон
class IObservable
{
public:
	virtual void RegisterObserver(const std::string& type, IObserver& observer) = 0;
	virtual void NotifyObservers(const std::string& type) = 0;
	virtual void RemoveObserver(const std::string& type, IObserver& observer) = 0;

	virtual ~IObservable() = default;
};

class IObserver
{
public:
	virtual void Update(IObservable& subj) = 0;
	virtual ~IObserver() = default;
};

class Observable : public IObservable
{
public:
	void RegisterObserver(const std::string& type, IObserver& observer) override
	{
		CheckTypeForAvailability(type);
		m_observers[type].insert(&observer);
	}

	void NotifyObservers(const std::string& type) override
	{
		CheckTypeForAvailability(type);
		auto observers = m_observers[type];
		for (auto* observer : observers)
		{
			observer->Update(*this);
		}
	}

	void RemoveObserver(const std::string& type, IObserver& observer) override
	{
		CheckTypeForAvailability(type);
		m_observers[type].erase(&observer);
	}

protected:
	void AddType(const std::string& type)
	{
		m_observers[type] = std::set<IObserver*>();
	}

private:
	std::map<std::string, std::set<IObserver*>> m_observers;
	void CheckTypeForAvailability(const std::string& type)
	{
		if (!m_observers.contains(type))
		{
			throw std::invalid_argument("Unknown type: " + type);
		}
	}
};

} // namespace Observer
