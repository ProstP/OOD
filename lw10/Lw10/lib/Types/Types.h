#pragma once

namespace Types
{

struct Point
{
	int x;
	int y;
};

struct Rect
{
	int left;
	int top;
	unsigned width;
	unsigned height;
};

const int CANVAS_WIDTH = 640;
const int CANVAS_HEIGHT = 480;

} // namespace Shapes
