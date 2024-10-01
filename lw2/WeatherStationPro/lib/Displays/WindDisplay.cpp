#include "WindDisplay.h"

void Displays::WindDisplay::SetWd(WeatherStation::WeatherDataPro& wd)
{
	m_wd = &wd;
	m_wd->RegisterObserver("WindSpeed", *this);
	m_wd->RegisterObserver("WindDirection", *this);
}

void Displays::WindDisplay::Update(Observer::IObservable& subj)
{
	if (m_wd != &subj)
	{
		return;
	}

	std::cout << "Wind display: " << std::endl
			  << "Speed: " << m_wd->GetWindSpeed() << std::endl
			  << "Direction: " << m_wd->GetWindDirection() << std::endl;
	std::cout << "<---------------->" << std::endl;
}
