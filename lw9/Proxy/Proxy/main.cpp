#include "../lib/Drawer/Drawer.h"
#include <iostream>

int main()
{
	Image image({ 49, 49 }, 0xffff00);

	//Drawer::DrawLine(image, { 1, 1 }, { 1, 5 }, '%');
	//Drawer::DrawCircle(image, { 24, 24 }, 24, '%');
	Drawer::FillCircle(image, { 24, 30 }, 5, 0x0000ff);
	//image.SetPixel({ 24, 24 }, 0xff0011);
	Drawer::DrawLine(image, { 10, 10 }, { 40, 40 }, 0xff0000);
	Drawer::DrawCircle(image, { 20, 10 }, 10, 0x00ff00);

	SaveImage(image, "output.ppm");
	//Print(image, std::cout);
}
