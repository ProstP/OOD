#pragma once
#include "../Observer/Observer.h"
#include "../WeatherStation/WeatherData.h"

namespace Displays
{

class HumidityDisplay : public Observer::IObserver
{
public:
	void SetWd(WeatherStation::WeatherData& wd);
	void Update(Observer::IObservable& subj) override;

	~HumidityDisplay();

private:
	WeatherStation::WeatherData* m_wd;
};

} // namespace Displays
