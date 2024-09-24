#include "Display.h"
#include <iostream>

void Displays::Display::Update(const WeatherStation::WeatherInfo& data)
{
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}
