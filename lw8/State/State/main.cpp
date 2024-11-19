#include <iostream>
#include "../lib/GamBallMachine/GumBallMachine.h"

using namespace GamBallMachine;

int main()
{
	GumballMachine machine(0);

	std::cout << machine.ToString();
}