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
	double GetTemperature() const;
	// ������������� ��������� (0...100)
	double GetHumidity() const;
	// ����������� �������� (� ��.��.��)
	double GetPressure() const;

	void MeasurementsChanged();

	void SetMeasurements(double temp, double humidity, double pressure);

	~WeatherData() = default;

protected:
	WeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

} // namespace WeatherStation
