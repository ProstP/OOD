#include "Image.h"

void Shapes::Image::AddShape(std::shared_ptr<Shape> shape)
{
	m_shapes.push_back(shape);
}

void Shapes::Image::DeleteAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

size_t Shapes::Image::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<Shapes::Shape> Shapes::Image::GetAt(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index out of range");
	}

	return m_shapes[index];
}
