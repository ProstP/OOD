#pragma once
#include "../Observer/Observer.h"
#include "../WeatherStation/WeatherData.h"
#include "../WeatherStation/WeatherInfo.h"

namespace Displays
{

class DuoDisplay : public Observer::IObserver<WeatherStation::WeatherInfo>
{
public:
	void SetInWeatherData(WeatherStation::WeatherData& wd);
	void SetOutWeatherData(WeatherStation::WeatherData& wd);
	~DuoDisplay();

private:
	WeatherStation::WeatherData* m_inWd;
	WeatherStation::WeatherData* m_outWd;
	void Update(Observer::IObservable<WeatherStation::WeatherInfo>& subj) override;
	void static PrintData(const WeatherStation::WeatherInfo& data);
};

} // namespace Displays
