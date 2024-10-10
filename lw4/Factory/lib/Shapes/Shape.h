#pragma once
#include "../Canvas/ICanvas.h"
#include "Color.h"
#include <string>

namespace Shapes
{

class Shape
{
public:
	void SetColor(const std::string& color);
	Color GetColor() const;
	virtual void Draw(Canvas::ICanvas& canvas) = 0;

private:
	Color m_color = Color::Black;
};

} // namespace Shapes
