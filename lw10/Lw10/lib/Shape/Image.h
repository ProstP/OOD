#pragma once
#include "Shape.h"
#include <iostream>
#include <vector>

namespace Shapes
{

class Image
{
public:
	void AddShape(std::shared_ptr<Shape> shape);
	void DeleteAtIndex(size_t index);
	size_t GetShapesCount() const;
	std::shared_ptr<Shape> GetAt(size_t index) const;

private:
	std::vector<std::shared_ptr<Shape>> m_shapes;
};

} // namespace Shapes
