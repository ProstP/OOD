#pragma once
#include "../Shapes/Color.h"
#include "../Shapes/Point.h"

namespace Canvas
{

class ICanvas
{
public:
	virtual void DrawLine(const Shapes::Point& start, const Shapes::Point& end) = 0;
	virtual void DrawEllipse(const Shapes::Point& center, double hr, double vr) = 0;
	virtual void SetColor(Shapes::Color color) = 0;

	virtual ~ICanvas() = default;
};//Длбавить деструктуры

} // namespace Canvas
