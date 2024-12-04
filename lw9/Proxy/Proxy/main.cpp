#include "../lib/Drawer/Drawer.h"
#include <iostream>

int main()
{
	Image image({ 49, 49 }, '*');

	//Drawer::DrawLine(image, { 1, 1 }, { 1, 5 }, '%');
	//Drawer::DrawCircle(image, { 24, 24 }, 24, '%');
	Drawer::FillCircle(image, { 24, 24 }, 24, '%');
	image.SetPixel({ 24, 24 }, '@');

	Print(image, std::cout);
}
