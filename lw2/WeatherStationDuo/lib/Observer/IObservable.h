#pragma once
#include "IObserver.h"
#include <iostream>
#include <set>

namespace Observer
{

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

} // namespace Observer
