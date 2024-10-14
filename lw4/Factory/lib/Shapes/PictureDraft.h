#pragma once
#include "Shape.h"
#include <memory>
#include <vector>

namespace Shapes
{

class PictureDraft
{
public:
	typedef std::vector<std::unique_ptr<Shape>> Shapes;

	Shapes::iterator begin();
	Shapes::iterator end();

	Shapes::const_iterator cbegin();
	Shapes::const_iterator cend();

	void AddShape(std::unique_ptr<Shape>&& shape);

private:
	Shapes m_shapes;
};

} // namespace Shapes
