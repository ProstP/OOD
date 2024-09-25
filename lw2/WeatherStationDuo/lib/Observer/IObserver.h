#pragma once

namespace Observer
{

template <typename T>
class IObserver
{
public:
	virtual void Update(IObservable<T>& subj) = 0;
	virtual ~IObserver() = default;
};

} // namespace Observer
