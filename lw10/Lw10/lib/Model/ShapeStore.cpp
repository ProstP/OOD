#include "ShapeStore.h"

void Model::ShapeStore::AddShape(const std::string& shape)
{
	m_shapes.push_back(m_factory.CreateShape(shape));
}

void Model::ShapeStore::DeleteAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

size_t Model::ShapeStore::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<Shapes::Shape> Model::ShapeStore::GetAt(size_t index) const
{
	if (index >= m_shapes.size())
	{
		return nullptr;
	}

	return m_shapes[index];
}
