#include "PressureDisplay.h"

void Displays::PressureDisplay::SetWd(WeatherStation::WeatherData& wd)
{
	m_wd = &wd;
	m_wd->RegisterObserver("Pressure", *this);
}

void Displays::PressureDisplay::Update(Observer::IObservable& subj)
{
	if (m_wd != &subj)
	{
		return;
	}

	std::cout << "Pressure display: " << m_wd->GetPressure() << std::endl;
	std::cout << "<---------------->" << std::endl;
}
