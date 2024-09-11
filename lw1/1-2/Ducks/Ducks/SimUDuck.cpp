#include "lib/Handler/DuckHandler.h"
#include "lib/SamplesDuck/DecoyDuck.h"
#include "lib/SamplesDuck/MallardDuck.h"
#include "lib/SamplesDuck/ModelDuck.h"
#include "lib/SamplesDuck/RedheadDuck.h"
#include "lib/SamplesDuck/RubberDuck.h"
#include <iostream>

int main()
{
	DecoyDuck decoyDuck;
	HandleDuck(decoyDuck);
	ModelDuck modelDuck;
	HandleDuck(modelDuck);
	RubberDuck rubberDuck;
	HandleDuck(rubberDuck);
	ReheadDuck redheadDuck;
	HandleDuck(redheadDuck);
	MallardDuck mallardDuck;
	HandleDuck(mallardDuck);
}
