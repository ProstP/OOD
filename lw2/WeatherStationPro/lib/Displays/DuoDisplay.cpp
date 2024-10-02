#include "DuoDisplay.h"

void Displays::DuoDisplay::SetInWeatherData(WeatherStation::WeatherData& wd)
{
	m_inWd = &wd;
	m_inWd->RegisterObserver("Temperature", *this);
	m_inWd->RegisterObserver("Humidity", *this);
	m_inWd->RegisterObserver("Pressure", *this);
}

void Displays::DuoDisplay::SetOutWeatherData(WeatherStation::WeatherDataPro& wd)
{
	m_outWd = &wd;
	m_outWd->RegisterObserver("Temperature", *this);
	m_outWd->RegisterObserver("Humidity", *this);
	m_outWd->RegisterObserver("Pressure", *this);
	m_outWd->RegisterObserver("WindSpeed", *this);
	m_outWd->RegisterObserver("WindDirection", *this);
}

Displays::DuoDisplay::~DuoDisplay()
{
	m_inWd->RemoveObserver("Temperature", *this);
	m_inWd->RemoveObserver("Humidity", *this);
	m_inWd->RemoveObserver("Pressure", *this);
	m_outWd->RemoveObserver("Temperature", *this);
	m_outWd->RemoveObserver("Humidity", *this);
	m_outWd->RemoveObserver("Pressure", *this);
	m_outWd->RemoveObserver("WindSpeed", *this);
	m_outWd->RemoveObserver("WindDirection", *this);
	m_inWd = nullptr;
	m_outWd = nullptr;
}

void Displays::DuoDisplay::Update(Observer::IObservable& subj)
{
	if (m_inWd == &subj)
	{
		std::cout << "In:" << std::endl;
		PrintData("Temp", m_inWd->GetTemperature());
		PrintData("Humidity", m_inWd->GetHumidity());
		PrintData("Pressure", m_inWd->GetPressure());
	}
	if (m_outWd == &subj)
	{
		std::cout << "Out:" << std::endl;
		PrintData("Temp", m_outWd->GetTemperature());
		PrintData("Humidity", m_outWd->GetHumidity());
		PrintData("Pressure", m_outWd->GetPressure());
		PrintData("WindSpeed", m_outWd->GetWindSpeed());
		PrintData("WindDirection", m_outWd->GetWindDirection());
	}

	std::cout << "<---------------->" << std::endl;
}

void Displays::DuoDisplay::PrintData(const std::string& name, double value)
{
	std::cout << "Current " << name << ": " << value << std::endl;
}
