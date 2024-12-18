#pragma once
#include "../Factory/IShapeFactory.h"
#include "../Shape/Shape.h"
#include <iostream>
#include <vector>

namespace Model
{

class ShapeStore
{
public:
	ShapeStore(Factory::IShapeFactory& factory)
		: m_factory(factory)
	{
	}

	void AddShape(const std::string& shape);
	void DeleteAtIndex(size_t index);
	size_t GetShapesCount() const;
	std::shared_ptr<Shapes::Shape> GetAt(size_t index) const;

private:
	Factory::IShapeFactory& m_factory;
	std::vector<std::shared_ptr<Shapes::Shape>> m_shapes;
};

} // namespace Model
