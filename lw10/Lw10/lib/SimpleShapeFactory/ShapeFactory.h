#pragma once
#include "../Factory/IShapeFactory.h"

namespace SimpleShapeFactory
{

class ShapeFactory : public Factory::IShapeFactory
{
public:
	std::shared_ptr<Shapes::Shape> CreateShape(const std::string& shape) override;
};

} // namespace SimpleShapeFactory
