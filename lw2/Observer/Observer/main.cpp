#include "../lib/Displays/Display.h"
#include "../lib/Displays/StatsDisplay.h"
#include "../lib/WeatherStation/WeatherStation.h"
#include <iostream>

using namespace Displays;
using namespace WeatherStation;

int main()
{
	WeatherData wd;

	Display d;
	wd.RegisterObserver(d);

	StatsDisplay sd;
	wd.RegisterObserver(sd);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(d);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);

	return 0;
}
