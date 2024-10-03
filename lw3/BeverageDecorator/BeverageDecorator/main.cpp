#include "../lib/Coffee/Coffee.h"
#include "../lib/Condiment/Condiment.h"
#include "../lib/MilkShake/MilkShake.h"
#include "../lib/Tea/Tea.h"
#include <functional>
#include <iostream>

using namespace Tea;
using namespace MilkShake;
using namespace Coffee;
using namespace Condiment;

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&... args)
{
	return [=](auto&& b) {
		return std::make_unique<Condiment>(std::move(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(std::move(component));
}

int main()
{
	auto capWithLiqAndChoc = std::make_unique<DoubleCappuccino>() << MakeCondiment<Liquor>(LiquorType::Nutty) << MakeCondiment<Chocolate>(3);

	auto latteWithChoc = std::make_unique<DoubleLatte>() << MakeCondiment<Chocolate>(3);

	std::cout << capWithLiqAndChoc->GetDescription() << "cost: " << capWithLiqAndChoc->GetCost() << std::endl;
	std::cout << latteWithChoc->GetDescription() << "cost: " << latteWithChoc->GetCost() << std::endl;
}
