#pragma once
#include "../Shapes/Shape.h"
#include <memory>
#include <string>

namespace ShapeFactory
{

class IShapeFactory
{
public:
	virtual std::shared_ptr<Shapes::Shape> CreateShape(const std::string& type, const std::string& params) = 0;
};

} // namespace ShapeFactory
