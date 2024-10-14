#pragma once
#include "../Factory/IShapeFactory.h"
#include "SimpleShapes.h"
#include <set>
#include <regex>

namespace SimpleShapeFactory
{

class SimpleShapeFactory : public ShapeFactory::IShapeFactory
{
public:
	std::unique_ptr<Shapes::Shape> CreateShape(const std::string& shape) override;

	~SimpleShapeFactory() override = default;

private:
	void ParseParametrs(const std::string& str, std::smatch& m, const std::regex& pattern);
};

} // namespace SimpleShapeFactory
