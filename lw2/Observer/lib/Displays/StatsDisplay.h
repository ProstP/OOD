#pragma once
#include "../Observer/IObserver.h"
#include "../WeatherStation/WeatherInfo.h"
#include <algorithm>
#include <climits>

namespace Displays
{

class StatsDisplay : public Observer::IObserver<WeatherStation::WeatherInfo>
{
private:
	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accTemperature = 0;
	double m_minHumidity = std::numeric_limits<double>::infinity();
	double m_maxHumidity = -std::numeric_limits<double>::infinity();
	double m_accHumidity = 0;
	double m_minPressure = std::numeric_limits<double>::infinity();
	double m_maxPressure = -std::numeric_limits<double>::infinity();
	double m_accPressure = 0;
	unsigned m_countAcc = 0;

	void Update(const WeatherStation::WeatherInfo& data) override;
	void UpdateData(const WeatherStation::WeatherInfo& data);
	void static UpdateBounds(double& min, double& max, double value);
};

} // namespace Displays
