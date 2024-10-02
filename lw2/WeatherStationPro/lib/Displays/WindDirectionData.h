#pragma once
#include "IStatData.h"
#include <iostream>

namespace Displays
{

class WindDirectionData : public IStatData
{
public:
	void Update(double value) override;
	double GetMin() const override;
	double GetMax() const override;
	double GetAverage() const override;

	~WindDirectionData() = default;

private:
	double m_min = 360;
	double m_max = 0;
	double m_average = 0;
};

} // namespace Displays
