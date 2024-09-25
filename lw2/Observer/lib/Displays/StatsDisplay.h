#pragma once
#include "../Observer/IObserver.h"
#include "../WeatherStation/WeatherInfo.h"
#include <algorithm>
#include <climits>
#include <iostream>

namespace Displays
{

class StatsDisplay : public Observer::IObserver<WeatherStation::WeatherInfo>
{
public:
	~StatsDisplay() = default;

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
	void PrintData();
	void static UpdateBounds(double& min, double& max, double value);
	void static PrintStatData(const std::string& name, double min, double max, double average);
};

} // namespace Displays
