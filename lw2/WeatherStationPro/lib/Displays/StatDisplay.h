#pragma once
#include "../Observer/Observer.h"
#include "../WeatherStation/WeatherDataPro.h"
#include "IStatData.h"

namespace Displays
{

class StatDisplay : public Observer::IObserver
{
public:
	StatDisplay();
	void SetWd(WeatherStation::WeatherDataPro& wd);

	~StatDisplay();

private:
	WeatherStation::WeatherDataPro* m_wd;
	std::map<std::string, std::unique_ptr<IStatData>> m_statDatas;
	void Update(Observer::IObservable& subj) override;
	void UpdateData();
	void PrintData() const;
	void PrintDataByName(const std::string& name) const;
};

} // namespace Displays
