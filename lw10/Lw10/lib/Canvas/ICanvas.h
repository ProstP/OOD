#pragma once
#include "../Types/Types.h"
#include <vector>

namespace Canvas
{
class ICanvas
{
public:
	virtual void DrawEllipse(Types::Rect rect) = 0;
	virtual void DrawPolygon(const std::vector<Types::Point>& points) = 0;

	virtual ~ICanvas() = default;
};
} // namespace Canvas
