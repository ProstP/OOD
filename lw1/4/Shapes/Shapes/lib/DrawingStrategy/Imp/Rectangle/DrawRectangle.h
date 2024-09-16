#pragma once
#include "../../IDrawingStrategy.h"

class DrawRectangle : public IDrawingStrategy
{
public:
	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~DrawRectangle() = default;
};
