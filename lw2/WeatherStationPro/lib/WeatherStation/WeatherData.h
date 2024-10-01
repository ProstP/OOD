#pragma once
#include "../Observer/Observer.h"

namespace WeatherStation
{

class WeatherData : public Observer::Observable
{
public:
	WeatherData();

	double GetTemperature() const;
	double GetHumidity() const;
	double GetPressure() const;

	void SetTemperature(double value);
	void SetHumidity(double value);
	void SetPressure(double value);

	~WeatherData() = default;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

} // namespace WeatherStation
