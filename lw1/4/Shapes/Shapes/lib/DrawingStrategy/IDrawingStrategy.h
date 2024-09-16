#pragma once
#include "../Gfx/ICanvas.h"

class IDrawingStrategy
{
public:
	virtual void Draw(ICanvas& canvas){};
	virtual void MoveTo(double dx, double dy){};
	virtual std::string GetType() const { return std::string(); };
	virtual std::string GetParams() const { return std::string(); };
	virtual ~IDrawingStrategy() = default;
};
