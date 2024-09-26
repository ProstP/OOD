#pragma once
#include "../Observer/Observer.h"
#include "WeatherInfo.h"

namespace WeatherStation
{

class WeatherData : public Observer::Observable<WeatherInfo>
{
public:
	double GetTemperature() const;
	double GetHumidity() const;
	double GetPressure() const;

	void MeasurementsChanged();

	void SetMeasurements(double temp, double humidity, double pressure);

	~WeatherData() = default;

	WeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

} // namespace WeatherStation
