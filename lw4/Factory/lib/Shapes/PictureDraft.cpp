#include "PictureDraft.h"

void Shapes::PictureDraft::AddShape(std::shared_ptr<Shape> shape)
{
	m_shapes.push_back(shape);
}

int Shapes::PictureDraft::GetShapeCount() const
{
	return static_cast<int>(m_shapes.size());
}

std::shared_ptr<Shapes::Shape> Shapes::PictureDraft::GetShape(int index) const
{
	return m_shapes[index];
}
