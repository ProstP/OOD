#include "../lib/Drawer/Drawer.h"
#include <iostream>

int main()
{
	Image image({ 50, 30 }, 0x42c4e0);

	Drawer::DrawLine(image, { 0, 30 }, { 50, 30 }, 0x4cdc38);
	Drawer::DrawLine(image, { 0, 29 }, { 50, 29 }, 0x4cdc38);
	Drawer::DrawLine(image, { 0, 28 }, { 50, 28 }, 0x4cdc38);
	Drawer::DrawLine(image, { 0, 27 }, { 50, 27 }, 0x4cdc38);
	Drawer::DrawLine(image, { 0, 26 }, { 50, 26 }, 0x4cdc38);
	Drawer::DrawLine(image, { 0, 25 }, { 50, 25 }, 0x4cdc38);

	Drawer::DrawLine(image, { 15, 25 }, { 35, 25 }, 0xdcb638);
	Drawer::DrawLine(image, { 15, 25 }, { 15, 12 }, 0xdcb638);
	Drawer::DrawLine(image, { 35, 25 }, { 35, 12 }, 0xdcb638);

	Drawer::DrawLine(image, { 10, 12 }, { 40, 12 }, 0xdc7b38);
	Drawer::DrawLine(image, { 10, 12 }, { 25, 5 }, 0xdc7b38);
	Drawer::DrawLine(image, { 26, 5 }, { 40, 12 }, 0xdc7b38);

	Drawer::DrawCircle(image, { 25, 18 }, 4, 0x3d79ff);

	Drawer::FillCircle(image, { 5, 5 }, 4, 0xf0f0f0);
	Drawer::FillCircle(image, { 45, 8 }, 3, 0xf0f0f0);

	SaveImage(image, "output.ppm");
}
