#pragma once
#include "../../IDrawingStrategy.h"

class DrawTextStrategy : public IDrawingStrategy
{
public:
	DrawTextStrategy(const std::string& params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~DrawTextStrategy() = default;

private:
	double m_left;
	double m_top;
	int m_fontSize;
	std::string m_text;
};
