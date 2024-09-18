#pragma once
#include "../../IFigure.h"

class Line : public IFigure
{
public:
	Line(const std::string params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~Line() = default;

private:
	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;
};
