#include "StatData.h"

void Displays::StatData::Update(double value)
{
	if (value < m_min)
	{
		m_min = value;
	}
	if (value > m_max)
	{
		m_max = value;
	}
	m_acc += value;
	m_count++;
}

double Displays::StatData::GetMin() const
{
	return m_min;
}

double Displays::StatData::GetMax() const
{
	return m_max;
}

double Displays::StatData::GetAverage() const
{
	return m_acc / m_count;
}
