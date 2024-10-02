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
	double GetWindDirection();

	void SetWindSpeed(double value);
	void SetWindDirection(double value);

	~WeatherDataPro() = default;

private:
	double m_windSpeed = 0;
	double m_windDirection = 0;
};

} // namespace WeatherStation
