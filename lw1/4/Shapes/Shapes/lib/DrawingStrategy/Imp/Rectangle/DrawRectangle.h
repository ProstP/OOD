#pragma once
#include "../../IDrawingStrategy.h"

class DrawRectangle : public IDrawingStrategy
{
public:
	DrawRectangle(const std::string& params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~DrawRectangle() = default;

private:
	double m_left;
	double m_top;
	double m_width;
	double m_height;
};
