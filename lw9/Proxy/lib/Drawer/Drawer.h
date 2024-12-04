#pragma once
#include "../Image/Image.h"

class Drawer
{
public:
	static void DrawLine(Image& image, const Point& from, const Point& to, char color);
	static void DrawCircle(Image& image, Point center, int radius, char color);
	static void FillCircle(Image& image, Point center, int radius, char color);

private:
	static void DrawSteepLine(Image& image, Point from, Point to, char color);
	static void DrawSlopeLine(Image& image, Point from, Point to, char color);
};
