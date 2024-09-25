#include "StatsDisplay.h"

void Displays::StatsDisplay::Update(const WeatherStation::WeatherInfo& data)
{

	UpdateData(data);

	PrintData();
}

void Displays::StatsDisplay::UpdateData(const WeatherStation::WeatherInfo& data)
{
	UpdateBounds(m_minTemperature, m_maxTemperature, data.temperature);
	m_accTemperature += data.temperature;

	UpdateBounds(m_minHumidity, m_maxHumidity, data.humidity);
	m_accHumidity += data.humidity;

	UpdateBounds(m_minPressure, m_maxPressure, data.pressure);
	m_accPressure += data.pressure;

	m_countAcc++;
}

void Displays::StatsDisplay::PrintData()
{
	PrintStatData("Temp", m_minTemperature, m_maxTemperature, (m_accTemperature / m_countAcc));
	PrintStatData("Humidity", m_minHumidity, m_maxHumidity, (m_accHumidity/ m_countAcc));
	PrintStatData("Pressure", m_minPressure, m_maxPressure, (m_accPressure/ m_countAcc));
	std::cout << "----------------" << std::endl;
}

void Displays::StatsDisplay::UpdateBounds(double& min, double& max, double value)
{
	if (min > value)
	{
		min = value;
	}
	if (max < value)
	{
		max = value;
	}
}

void Displays::StatsDisplay::PrintStatData(const std::string& name, double min, double max, double average)
{
	std::cout << "Max " << name << " " << max << std::endl;
	std::cout << "Min " << name << " " << min << std::endl;
	std::cout << "Average " << name << " " << average << std::endl;
	std::cout << "- - - - - - - -" << std::endl;
}
