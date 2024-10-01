#pragma once
#include "../Observer/Observer.h"
#include "../WeatherStation/WeatherData.h"

namespace Displays
{

class TempDisplay : public Observer::IObserver
{
public:
	void SetWd(WeatherStation::WeatherData& wd);
	void Update(Observer::IObservable& subj) override;

private:
	WeatherStation::WeatherData* m_wd;
};

} // namespace Displays
