#pragma once
#include "../../IDrawingStrategy.h"

class DrawTriangle : public IDrawingStrategy
{
public:
	DrawTriangle(const std::string& params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~DrawTriangle() = default;

private:
	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;
	double m_x3;
	double m_y3;
};
