#include "SimpleShapeFactory.h"
#include <iostream>

std::unique_ptr<Shapes::Shape> SimpleShapeFactory::SimpleShapeFactory::CreateShape(const std::string& shape)
{
	const std::regex pattern("^(\\w+)\\s+(.+)$");

	std::smatch m;
	if (!std::regex_match(shape, m, pattern))
	{
		throw std::invalid_argument("Invalid command to create shape");
	}

	std::string type = m[1].str();
	std::string params = m[2].str();

	try
	{
		if (type == "rectangle")
		{
			std::smatch match;
			ParseParametrs(params, match, std::regex("^\\s*(\\w+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*$"));
			std::string color = match[1].str();
			double ltx = std::stod(match[2]);
			double lty = std::stod(match[3]);
			double rbx = std::stod(match[4]);
			double rby = std::stod(match[5]);

			return std::make_unique<Rectangle>(color, ltx, lty, rbx, rby);
		}
		else if (type == "triangle")
		{
			std::smatch match;
			ParseParametrs(params, match,
				std::regex("^\\s*(\\w+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*$"));
			std::string color = match[1].str();
			double v1x = std::stod(match[2]);
			double v1y = std::stod(match[3]);
			double v2x = std::stod(match[4]);
			double v2y = std::stod(match[5]);
			double v3x = std::stod(match[6]);
			double v3y = std::stod(match[7]);

			return std::make_unique<Triangle>(color, v1x, v1y, v2x, v2y, v3x, v3y);
		}
		else if (type == "ellipse")
		{
			std::smatch match;
			ParseParametrs(params, match, std::regex("^\\s*(\\w+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*$"));
			std::string color = match[1].str();
			double cx = std::stod(match[2]);
			double cy = std::stod(match[3]);
			double hr = std::stod(match[4]);
			double hv = std::stod(match[5]);

			return std::make_unique<Ellipse>(color, cx, cy, hr, hv);
		}
		else if (type == "regularpolygon")
		{
			std::smatch match;
			ParseParametrs(params, match, std::regex("^\\s*(\\w+)\\s*(\-?[\\d\.]+)\\s*(\-?[\\d\.]+)\\s*([\\d\.]+)\\s*([\\d\.]+)\\s*$"));
			std::string color = match[1].str();
			double cx = std::stod(match[2]);
			double cy = std::stod(match[3]);
			double r = std::stod(match[4]);
			double count = std::stoi(match[5]);

			return std::make_unique<RegularPolygon>(color, cx, cy, r, count);
		}
		else
		{
			throw std::invalid_argument("Uknown type of shape " + type);
		}
	}
	catch (...)
	{
		throw std::invalid_argument("Invalid parametrs for shape");
	}
}

void SimpleShapeFactory::SimpleShapeFactory::ParseParametrs(const std::string& str, std::smatch& m, const std::regex& pattern)
{
	if (!std::regex_match(str, m, pattern))
	{
		throw std::invalid_argument("Invalid parameters for rectangle");
	}
}
