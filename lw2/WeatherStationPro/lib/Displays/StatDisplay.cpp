#include "StatDisplay.h"
#include "StatData.h"
#include "WindDirectionData.h"

Displays::StatDisplay::StatDisplay()
{
	m_wd = nullptr;
	m_statDatas["Temperature"] = std::make_unique<StatData>();
	m_statDatas["Humidity"] = std::make_unique<StatData>();
	m_statDatas["Pressure"] = std::make_unique<StatData>();
	m_statDatas["WindSpeed"] = std::make_unique<StatData>();
	m_statDatas["WindDirection"] = std::make_unique<WindDirectionData>();
}

void Displays::StatDisplay::SetWd(WeatherStation::WeatherDataPro& wd)
{
	m_wd = &wd;
	m_wd->RegisterObserver("Temperature", *this);
	m_wd->RegisterObserver("Humidity", *this);
	m_wd->RegisterObserver("Pressure", *this);
	m_wd->RegisterObserver("WindSpeed", *this);
	m_wd->RegisterObserver("WindDirection", *this);
}

Displays::StatDisplay::~StatDisplay()
{
	m_wd->RemoveObserver("Temperature", *this);
	m_wd->RemoveObserver("Humidity", *this);
	m_wd->RemoveObserver("Pressure", *this);
	m_wd->RemoveObserver("WindSpeed", *this);
	m_wd->RemoveObserver("WindDirection", *this);
	m_wd = nullptr;
}

void Displays::StatDisplay::Update(Observer::IObservable& subj)
{
	UpdateData();

	PrintData();
}

void Displays::StatDisplay::UpdateData()
{
	m_statDatas["Temperature"]->Update(m_wd->GetTemperature());
	m_statDatas["Humidity"]->Update(m_wd->GetHumidity());
	m_statDatas["Pressure"]->Update(m_wd->GetPressure());
	m_statDatas["WindSpeed"]->Update(m_wd->GetWindSpeed());
	m_statDatas["WindDirection"]->Update(m_wd->GetWindDirection());
}

void Displays::StatDisplay::PrintData() const
{
	PrintDataByName("Temperature");
	PrintDataByName("Humidity");
	PrintDataByName("Pressure");
	PrintDataByName("WindSpeed");
	PrintDataByName("WindDirection");
	std::cout << "<-------------->" << std::endl;
}

void Displays::StatDisplay::PrintDataByName(const std::string& name) const
{
	std::cout << "Max " << name << " " << m_statDatas.at(name)->GetMax() << std::endl;
	std::cout << "Min " << name << " " << m_statDatas.at(name)->GetMin() << std::endl;
	std::cout << "Average " << name << " " << m_statDatas.at(name)->GetAverage() << std::endl;
	std::cout << "- - - - - - - -" << std::endl;
}
