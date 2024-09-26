#include <iostream>
#include "../lib/Displays/DuoDisplay.h"
#include "../lib/WeatherStation/WeatherData.h"

int main()
{
	WeatherStation::WeatherData inWd;
	WeatherStation::WeatherData outWd;

	Displays::DuoDisplay d;

	d.SetInWeatherData(inWd);
	d.SetOutWeatherData(outWd);

	inWd.SetMeasurements(22, 0.7, 760);
	outWd.SetMeasurements(4, 0.8, 761);

	outWd.SetMeasurements(0, 0.9, 763);
	inWd.SetMeasurements(21, 0.6, 765);

	return 0;
}
