#include "SimpleShapeFactory.h"
#include <iostream>

std::shared_ptr<Shapes::Shape> SimpleShapeFactory::SimpleShapeFactory::CreateShape(const std::string& type, const std::string& params)
{
	if (type == "rectangle")
	{
		return std::make_shared<Rectangle>(Rectangle(params));
	}
	else if (type == "triangle")
	{
		return std::make_shared<Triangle>(Triangle(params));
	}
	else if (type == "ellipse")
	{
		return std::make_shared<Ellipse>(Ellipse(params));
	}
	else if (type == "regularpolygon")
	{
		return std::make_shared<RegularPolygon>(RegularPolygon(params));
	}
	else
	{
		throw std::invalid_argument("Uknown type of shape " + type);
	}
}
