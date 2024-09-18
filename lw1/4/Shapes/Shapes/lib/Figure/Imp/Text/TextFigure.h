#pragma once
#include "../../IFigure.h"

class TextFigure : public IFigure
{
public:
	TextFigure(const std::string& params);

	void Draw(ICanvas& canvas) override;
	void MoveTo(double dx, double dy) override;
	std::string GetType() const override;
	std::string GetParams() const override;

	~TextFigure() = default;

private:
	double m_left;
	double m_top;
	int m_fontSize;
	std::string m_text;
};
