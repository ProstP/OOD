#include "SimpleShapeFactory.h"
#include <iostream>

std::shared_ptr<Shapes::Shape> SimpleShapeFactory::SimpleShapeFactory::CreateShape(const std::string& type, const std::string& params)
{
	if (type == "rectangle")
	{
		return std::make_shared<Shapes::Shape>(Rectangle(params));
	}
	else if (type == "triangle")
	{
		return std::make_shared<Shapes::Shape>(Triangle(params));
	}
	else if (type == "ellipse")
	{
		return std::make_shared<Shapes::Shape>(Ellipse(params));
	}
	else if (type == "regularpolygon")
	{
		return std::make_shared<Shapes::Shape>(RegularPolygon(params));
	}
	else
	{
		throw std::invalid_argument("Uknown type of shape " + type);
	}
}
