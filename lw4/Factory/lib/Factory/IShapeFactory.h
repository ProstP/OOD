#pragma once
#include "../Shapes/Shape.h"
#include <memory>
#include <string>

namespace ShapeFactory
{

class IShapeFactory
{
public:
	virtual std::unique_ptr<Shapes::Shape> CreateShape(const std::string& shape) = 0;

	virtual ~IShapeFactory() = default;
};

} // namespace ShapeFactory
