#include "Drawer.h"

int Sign(int value)
{
	return (0 < value) - (value < 0);
}

void Drawer::DrawLine(Image& image, const Point& from, const Point& to, char color)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	if (deltaY > deltaX)
	{
		DrawSteepLine(image, from, to, color);
	}
	else
	{
		DrawSlopeLine(image, from, to, color);
	}
}

void Drawer::DrawCircle(Image& image, Point center, int radius, char color)
{
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= x)
	{
		image.SetPixel({ center.x + x, center.y + y }, color);
		image.SetPixel({ center.x + x, center.y - y }, color);
		image.SetPixel({ center.x - x, center.y + y }, color);
		image.SetPixel({ center.x - x, center.y - y }, color);
		image.SetPixel({ center.x + y, center.y + x }, color);
		image.SetPixel({ center.x + y, center.y - x }, color);
		image.SetPixel({ center.x - y, center.y + x }, color);
		image.SetPixel({ center.x - y, center.y - x }, color);

		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0)
		{
			delta += (2 * ++x + 1);
		}
		else if (delta > 0 && error > 0)
		{
			delta -= (2 * --y + 1);
		}
		else
		{
			delta += (2 * (++x - --y));
		}
	}
}

void Drawer::FillCircle(Image& image, Point center, int radius, char color)
{
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= x)
	{
		for (int i = center.y - y; i <= center.y + y; i++)
		{
			image.SetPixel({ center.x + x, i }, color);
			image.SetPixel({ center.x - x, i }, color);
		}

		for (int i = center.x - y; i <= center.x + y; i++)
		{
			image.SetPixel({ i, center.y + x }, color);
			image.SetPixel({ i, center.y - x }, color);
		}

		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0)
		{
			delta += (2 * ++x + 1);
		}
		else if (delta > 0 && error > 0)
		{
			delta -= (2 * --y + 1);
		}
		else
		{
			delta += (2 * (++x - --y));
		}
	}
}

void Drawer::DrawSteepLine(Image& image, Point from, Point to, char color)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	assert(deltaY >= deltaX);

	if (from.y > to.y)
	{
		std::swap(from, to);
	}

	const int stepX = Sign(to.x - from.x);
	const int errorThreshold = deltaY + 1;
	const int deltaErr = deltaX + 1;

	int error = deltaErr / 2;

	for (Point p = from; p.y <= to.y; ++p.y)
	{
		image.SetPixel({ p.x, p.y }, color);
		assert((p.y != to.y) || (p.x == to.x));

		error += deltaErr;

		if (error >= errorThreshold)
		{
			p.x += stepX;
			error -= errorThreshold;
		}
	}
}

void Drawer::DrawSlopeLine(Image& image, Point from, Point to, char color)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	assert(deltaX >= deltaY);

	if (from.x > to.x)
	{
		std::swap(from, to);
	}

	const int stepY = Sign(to.y - from.y);
	const int errorThreshold = deltaX + 1;
	const int deltaErr = deltaY + 1;

	int error = deltaErr / 2;

	for (Point p = from; p.x <= to.x; ++p.x)
	{
		image.SetPixel({ p.x, p.y }, color);
		assert((p.x != to.x) || (p.y == to.y));

		error += deltaErr;

		if (error >= errorThreshold)
		{
			p.y += stepY;
			error -= errorThreshold;
		}
	}
}
