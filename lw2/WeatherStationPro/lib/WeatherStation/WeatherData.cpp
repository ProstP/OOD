#include "WeatherData.h"

WeatherStation::WeatherData::WeatherData()
{
	AddType("Temperature");
	AddType("Humidity");
	AddType("Pressure");
}

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

void WeatherStation::WeatherData::SetTemperature(double value)
{
	m_temperature = value;
	NotifyObservers("Temperature");
}

void WeatherStation::WeatherData::SetHumidity(double value)
{
	m_humidity = value;
	NotifyObservers("Humidity");
}

void WeatherStation::WeatherData::SetPressure(double value)
{
	m_pressure = value;
	NotifyObservers("Pressure");
}
