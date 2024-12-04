#pragma once
#include "../Image/Image.h"

class Drawer
{
public:
	static void DrawLine(Image& image, const Point& from, const Point& to, uint32_t color);
	static void DrawCircle(Image& image, Point center, int radius, uint32_t color);
	static void FillCircle(Image& image, Point center, int radius, uint32_t color);

private:
	static void DrawSteepLine(Image& image, Point from, Point to, uint32_t color);
	static void DrawSlopeLine(Image& image, Point from, Point to, uint32_t color);
};
