#pragma once
#include "../Gfx/ICanvas.h"

class IFigure
{
public:
	virtual void Draw(ICanvas& canvas){};
	virtual void MoveTo(double dx, double dy){};
	virtual std::string GetType() const { return std::string(); };
	virtual std::string GetParams() const { return std::string(); };
	virtual ~IFigure() = default;
};
