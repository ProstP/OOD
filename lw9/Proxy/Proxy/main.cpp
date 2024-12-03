#include "../lib/CoW/CoW.h"
#include <iostream>

int main()
{
	CoW<std::string> s1("Hello");
	CoW<std::string> s2(s1);

	s1.Write()->append("!!!");

	auto write = s1.Write();

	std::cout << *s1 << " " << *s2 << std::endl;
}
