#pragma once
#include "../../IDrawingStrategy.h"

class DrawCircle : public IDrawingStrategy
{
public:
	DrawCircle(std::string params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~DrawCircle() = default;

private:
	double m_x;
	double m_y;
	double m_r;
};
