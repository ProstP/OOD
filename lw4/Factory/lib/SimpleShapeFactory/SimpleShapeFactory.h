#pragma once
#include "../Factory/IShapeFactory.h"
#include "SimpleShapes.h"
#include <set>

namespace SimpleShapeFactory
{

class SimpleShapeFactory : ShapeFactory::IShapeFactory
{
public:
	std::shared_ptr<Shapes::Shape> CreateShape(const std::string& type, const std::string& params) override;
};

} // namespace SimpleShapeFactory
