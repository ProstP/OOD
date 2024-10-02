#pragma once
#include "IStatData.h"
#include <algorithm>

namespace Displays
{

class StatData : public IStatData
{
public:
	void Update(double value) override;
	double GetMin() const override;
	double GetMax() const override;
	double GetAverage() const override;

	~StatData() = default;

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	double m_count = 0;
};

} // namespace Displays
