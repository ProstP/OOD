#include "StatsDisplay.h"
#include <iostream>

void Displays::StatsDisplay::Update(const WeatherStation::WeatherInfo& data)
{

	UpdateData(data);

	std::cout << "Max Temp " << m_maxTemperature << std::endl;
	std::cout << "Min Temp " << m_minTemperature << std::endl;
	std::cout << "Average Temp " << (m_accTemperature / m_countAcc) << std::endl;
	std::cout << "Max Hum " << m_maxHumidity << std::endl;
	std::cout << "Min Hum " << m_minHumidity << std::endl;
	std::cout << "Average Hum " << (m_accHumidity / m_countAcc) << std::endl;
	std::cout << "Max Press " << m_maxPressure << std::endl;
	std::cout << "Min Press " << m_minPressure << std::endl;
	std::cout << "Average Press " << (m_accPressure / m_countAcc) << std::endl;
	std::cout << "----------------" << std::endl;
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
