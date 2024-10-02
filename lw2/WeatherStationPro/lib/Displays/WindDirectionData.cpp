#include "WindDirectionData.h"

void Displays::WindDirectionData::Update(double value)
{
	if (value < 0 || 359 < value)
	{
		throw std::invalid_argument("Wind direction must be between 0 and 359 degree");
	}

	if (value < m_min)
	{
		m_min = value;
	}
	if (value > m_max)
	{
		m_max = value;
	}

	//декартова системп координат
	if (abs(m_average - value < 180))
	{
		m_average = (m_average + value) / 2;
	}
	else
	{
		if (m_average > value)
		{
			value += 180;
		}
		else
		{
			m_average += 180;
		}

		m_average = (m_average + value) / 2;

		m_average = m_average > 359 ? m_average - 360 : m_average;
	}
}

double Displays::WindDirectionData::GetMin() const
{
	return m_min;
}

double Displays::WindDirectionData::GetMax() const
{
	return m_max;
}

double Displays::WindDirectionData::GetAverage() const
{
	return m_average;
}
