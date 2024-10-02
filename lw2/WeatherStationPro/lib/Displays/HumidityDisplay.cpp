#include "HumidityDisplay.h"

void Displays::HumidityDisplay::SetWd(WeatherStation::WeatherData& wd)
{
	m_wd = &wd;
	m_wd->RegisterObserver("Humidity", *this);
}

void Displays::HumidityDisplay::Update(Observer::IObservable& subj)
{
	if (m_wd != &subj)
	{
		return;
	}

	std::cout << "Humidity display: " << m_wd->GetHumidity() << std::endl;
	std::cout << "<---------------->" << std::endl;
}

Displays::HumidityDisplay::~HumidityDisplay()
{
	m_wd->RemoveObserver("Humidity", *this);
	m_wd = nullptr;
}
