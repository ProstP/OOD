#pragma once
#include "../Observer/IObservable.h"
#include "WeatherInfo.h"

using namespace Observer;

namespace WeatherStation
{

class WeatherData : public Observable<WeatherInfo>
{
public:
	// ����������� � �������� �������
	double GetTemperature() const
	{
		return m_temperature;
	}
	// ������������� ��������� (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// ����������� �������� (� ��.��.��)
	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	WeatherInfo GetChangedData() const override
	{
		WeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

} // namespace WeatherStation
