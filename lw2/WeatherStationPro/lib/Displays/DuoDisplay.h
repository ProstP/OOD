#pragma once
#include "../Observer/Observer.h"
#include "../WeatherStation/WeatherData.h"
#include "../WeatherStation/WeatherDataPro.h"

namespace Displays
{

class DuoDisplay : public Observer::IObserver
{
public:
	void SetInWeatherData(WeatherStation::WeatherData& wd);
	void SetOutWeatherData(WeatherStation::WeatherDataPro& wd);
	~DuoDisplay();

private:
	WeatherStation::WeatherData* m_inWd;
	WeatherStation::WeatherDataPro* m_outWd;
	void Update(Observer::IObservable& subj) override;
	void static PrintData(const std::string& name, double value);
};

} // namespace Displays
