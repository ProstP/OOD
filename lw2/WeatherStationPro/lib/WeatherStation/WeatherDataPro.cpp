#include "WeatherDataPro.h"

WeatherStation::WeatherDataPro::WeatherDataPro()
{
	AddType("WindSpeed");
	AddType("WindDirection");
}

double WeatherStation::WeatherDataPro::GetWindSpeed()
{
	return m_windSpeed;
}

double WeatherStation::WeatherDataPro::GetWindDirection()
{
	return m_windDirection;
}

void WeatherStation::WeatherDataPro::SetWindSpeed(double value)
{
	m_windSpeed = value;
	NotifyObservers("WindSpeed");
}

void WeatherStation::WeatherDataPro::SetWindDirection(double value)
{
	if (value < 0 || 359 < value)
	{
		throw std::invalid_argument("Wind direction must be between 0 and 360 degree");
	}
	m_windDirection = value;
	NotifyObservers("WindDirection");
}
