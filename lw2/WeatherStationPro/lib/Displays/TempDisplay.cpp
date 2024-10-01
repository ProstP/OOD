#include "TempDisplay.h"

void Displays::TempDisplay::SetWd(WeatherStation::WeatherData& wd)
{
	m_wd = &wd;
	m_wd->RegisterObserver("Temperature", *this);
}

void Displays::TempDisplay::Update(Observer::IObservable& subj)
{
	if (m_wd != &subj)
	{
		return;
	}

	std::cout << "Temp display: " << m_wd->GetTemperature() << std::endl;
	std::cout << "<---------------->" << std::endl;
}
