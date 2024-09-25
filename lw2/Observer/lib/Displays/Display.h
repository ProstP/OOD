#pragma once
#include "../Observer/IObserver.h"
#include "../WeatherStation/WeatherInfo.h"

namespace Displays
{

class Display : public Observer::IObserver<WeatherStation::WeatherInfo>
{
public:
	~Display() = default;

private:
	void Update(const WeatherStation::WeatherInfo& data) override;
};

} // namespace Displays
