#include "../lib/Displays/DuoDisplay.h"
#include "../lib/Displays/HumidityDisplay.h"
#include "../lib/Displays/PressureDisplay.h"
#include "../lib/Displays/StatDisplay.h"
#include "../lib/Displays/TempDisplay.h"
#include "../lib/Displays/WindDisplay.h"
#include "../lib/WeatherStation/WeatherData.h"
#include "../lib/WeatherStation/WeatherDataPro.h"
#include <iostream>

using namespace Displays;
using namespace WeatherStation;

int main()
{
	WeatherData wd;
	WeatherDataPro wdPro;

	TempDisplay td;
	HumidityDisplay hd;
	PressureDisplay pd;
	WindDisplay windD;
	StatDisplay sd;

	DuoDisplay duo;
	duo.SetInWeatherData(wd);
	duo.SetOutWeatherData(wdPro);

	td.SetWd(wdPro);
	windD.SetWd(wdPro);
	sd.SetWd(wdPro);

	hd.SetWd(wd);
	pd.SetWd(wd);

	wd.SetTemperature(20);
	wd.SetHumidity(80);
	wd.SetPressure(750);

	wdPro.SetTemperature(15);
	wdPro.SetHumidity(70);
	wdPro.SetPressure(770);
	wdPro.SetWindSpeed(10);
	wdPro.SetWindDirection(90);

	wdPro.RemoveObserver("Temperature", sd);
	wdPro.SetTemperature(20);
	wdPro.SetHumidity(75);
}
