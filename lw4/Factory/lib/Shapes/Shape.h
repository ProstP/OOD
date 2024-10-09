#pragma once
#include "../Canvas/ICanvas.h"
#include "Color.h"

namespace Shapes
{

class Shape
{
public:
	void SetColor(Color color);
	Color GetColor() const;
	virtual void Draw(Canvas::ICanvas& canvas) = 0;

private:
	Color m_color;
};

} // namespace Shapes
