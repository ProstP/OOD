#pragma once

namespace Observer
{

template <typename T>
class IObserver
{
public:
	virtual void Update(const T& data) = 0;
	virtual ~IObserver() = default;
};

} // namespace Observer
