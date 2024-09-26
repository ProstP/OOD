#include "DuoDisplay.h"

void Displays::DuoDisplay::SetInWeatherData(WeatherStation::WeatherData& wd)
{
	m_inWd = &wd;
	m_inWd->RegisterObserver(*this);
}

void Displays::DuoDisplay::SetOutWeatherData(WeatherStation::WeatherData& wd)
{
	m_outWd = &wd;
	m_outWd->RegisterObserver(*this);
}

Displays::DuoDisplay::~DuoDisplay()
{
	m_inWd = nullptr;
	m_outWd = nullptr;
}

void Displays::DuoDisplay::Update(Observer::IObservable<WeatherStation::WeatherInfo>& subj)
{
	if (m_inWd == &subj)
	{
		std::cout << "In:" << std::endl;
		PrintData(subj.GetChangedData());
	}
	if (m_outWd == &subj)
	{
		std::cout << "Out:" << std::endl;
		PrintData(subj.GetChangedData());
	}
}

void Displays::DuoDisplay::PrintData(const WeatherStation::WeatherInfo& data)
{
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}
