#pragma once
#include "WeatherData.h"
#include "WeatherDataPro.h"

namespace WeatherStation
{

class WeatherDataPro : public WeatherData
{
public:
	WeatherDataPro();

	double GetWindSpeed();
	int GetWindDirection();

	void SetWindSpeed(double value);
	void SetWindDirection(int value);

	~WeatherDataPro() = default;

private:
	double m_windSpeed = 0;
	int m_windDirection = 0;
};

} // namespace WeatherStation
