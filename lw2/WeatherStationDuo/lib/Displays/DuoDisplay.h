#pragma once
#include "../WeatherStation/WeatherData.h"

using namespace Observer;

namespace Displays
{

class DuoDisplay : public IObserver<WeatherStation::WeatherInfo>
{
public:
	void SetInWeatherData(WeatherStation::WeatherData& wd);
	void SetOutWeatherData(WeatherStation::WeatherData& wd);
	~DuoDisplay();

private:
	WeatherStation::WeatherData* m_inWd;
	WeatherStation::WeatherData* m_outWd;
	void Update(WeatherStation::WeatherData& subj) override;
	void static PrintData(const WeatherStation::WeatherInfo& data);
};

} // namespace Displays
