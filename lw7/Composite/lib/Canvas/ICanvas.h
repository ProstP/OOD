#pragma once
#include "../CommonTypes/CommonTypes.h"

using namespace CommonTypes;

namespace Canvas
{

class ICanvas
{
public:
	virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void SetOutlineColor(RGBAColor color) = 0;
	virtual void ClearOutlineColor() = 0;
	virtual void SetOutlineThickness(int thickness) = 0;
	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;

	virtual ~ICanvas() = default;
};

} // namespace Canvas
