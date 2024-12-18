#pragma once
#include "../Shape/Shape.h"
#include <memory>
#include <string>

namespace Factory
{

class IShapeFactory
{
public:
	virtual std::shared_ptr<Shapes::Shape> CreateShape(const std::string& shape) = 0;

	virtual ~IShapeFactory() = default;
};

} // namespace Factory
