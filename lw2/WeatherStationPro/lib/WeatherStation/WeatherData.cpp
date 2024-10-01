#include "WeatherData.h"

double WeatherStation::WeatherData::GetTemperature() const
{
	return m_temperature;
}

double WeatherStation::WeatherData::GetHumidity() const
{
	return m_humidity;
}

double WeatherStation::WeatherData::GetPressure() const
{
	return m_pressure;
}

void WeatherStation::WeatherData::MeasurementsChanged()
{
	NotifyObservers();
}

void WeatherStation::WeatherData::SetMeasurements(double temp, double humidity, double pressure)
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;

	MeasurementsChanged();
}

WeatherStation::WeatherInfo WeatherStation::WeatherData::GetChangedData() const
{
	WeatherInfo info;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	return info;
}
