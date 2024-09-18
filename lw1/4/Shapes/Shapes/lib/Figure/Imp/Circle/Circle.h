#pragma once
#include "../../IFigure.h"

class Circle : public IFigure
{
public:
	Circle(const std::string& params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~Circle() = default;

private:
	double m_x;
	double m_y;
	double m_r;
};
