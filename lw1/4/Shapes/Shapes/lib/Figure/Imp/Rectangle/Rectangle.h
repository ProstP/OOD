#pragma once
#include "../../IFigure.h"

class Rectangle : public IFigure
{
public:
	Rectangle(const std::string& params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~Rectangle() = default;

private:
	double m_left;
	double m_top;
	double m_width;
	double m_height;
};
