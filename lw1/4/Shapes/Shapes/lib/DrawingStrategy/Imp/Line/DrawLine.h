#pragma once
#include "../../IDrawingStrategy.h"

class DrawLine : public IDrawingStrategy
{
public:
	DrawLine(const std::string params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~DrawLine() = default;

private:
	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;
};
