#pragma once

namespace Displays
{

class IStatData
{
public:
	virtual void Update(double value) = 0;
	virtual double GetMin() const = 0;
	virtual double GetMax() const = 0;
	virtual double GetAverage() const = 0;

	virtual ~IStatData() = default;
};

} // namespace Displays
