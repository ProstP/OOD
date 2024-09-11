#include "../Duck/Duck.h"

void HandleDuck(const Duck& duck)
{
	duck.Swim();
	duck.Dance();
	duck.Fly();
	duck.Quack();
	duck.Display();
	std::cout << std::endl;
}
