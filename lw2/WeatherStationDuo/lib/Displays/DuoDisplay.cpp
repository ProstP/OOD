#include "DuoDisplay.h"

void Displays::DuoDisplay::SetInWeatherData(WeatherStation::WeatherData& wd)
{
	m_inWd = &wd;
}

void Displays::DuoDisplay::SetOutWeatherData(WeatherStation::WeatherData& wd)
{
	m_outWd = &wd;
}

Displays::DuoDisplay::~DuoDisplay()
{
	m_inWd = nullptr;
	m_outWd = nullptr;
}

void Displays::DuoDisplay::Update(WeatherStation::WeatherData& wd)
{
	if (m_inWd == &wd)
	{
		PrintData(wd.GetChangedData());
	}
	if (m_outWd == &wd)
	{
		PrintData(wd.GetChangedData());
	}
}

void Displays::DuoDisplay::PrintData(const WeatherStation::WeatherInfo& data)
{
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}
