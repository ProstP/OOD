#include "PictureDraft.h"

void Shapes::PictureDraft::AddShape(const Shapes::Shape& shape)
{
	m_shapes.push_back(std::make_shared<Shape>(shape));
}

int Shapes::PictureDraft::GetShapeCount() const
{
	return m_shapes.size();
}

std::shared_ptr<Shapes::Shape> Shapes::PictureDraft::GetShape(int index) const
{
	return m_shapes[index];
}
