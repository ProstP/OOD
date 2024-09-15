#pragma once
#include "../Gfx/ICanvas.h"

class IDrawingStrategy
{
public:
	virtual void Draw(ICanvas& canvas);
	virtual void MoveTo(double dx, double dy);
	virtual std::string ToString() const;
	virtual ~IDrawingStrategy() = default;
};
