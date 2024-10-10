#pragma once
#include "Shape.h"
#include <memory>
#include <vector>

namespace Shapes
{

class PictureDraft
{
public:
	void AddShape(std::shared_ptr<Shape> shape);
	int GetShapeCount() const;
	std::shared_ptr<Shape> GetShape(int index) const;

private:
	std::vector<std::shared_ptr<Shape>> m_shapes;
};

} // namespace Shapes
