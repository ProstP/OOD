#include "ShapeFactory.h"
#include "SimpleShapes.h"
#include <iostream>

std::shared_ptr<Shapes::Shape> SimpleShapeFactory::ShapeFactory::CreateShape(const std::string& shape)
{
	if (shape == "rectangle")
	{
		return std::make_shared<Rectangle>();
	}
	else if (shape == "ellipse")
	{
		return std::make_shared<Ellipse>();
	}
	else if (shape == "triangle")
	{
		return std::make_shared<Triangle>();
	}
	else
	{
		throw std::invalid_argument("Unknwon type of shape");
	}
}
