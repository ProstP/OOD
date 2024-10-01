#pragma once
#include "../Observer/Observer.h"
#include "../WeatherStation/WeatherDataPro.h"

namespace Displays
{

class WindDisplay : public Observer::IObserver
{
public:
	void SetWd(WeatherStation::WeatherDataPro& wd);
	void Update(Observer::IObservable& subj) override;

private:
	WeatherStation::WeatherDataPro* m_wd;
};

} // namespace Displays
