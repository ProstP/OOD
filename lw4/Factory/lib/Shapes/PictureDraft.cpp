#include "PictureDraft.h"

Shapes::PictureDraft::Shapes::iterator Shapes::PictureDraft::begin()
{
	return m_shapes.begin();
}

Shapes::PictureDraft::Shapes::iterator Shapes::PictureDraft::end()
{
	return m_shapes.end();
}

Shapes::PictureDraft::Shapes::const_iterator Shapes::PictureDraft::cbegin()
{
	return m_shapes.cbegin();
}

Shapes::PictureDraft::Shapes::const_iterator Shapes::PictureDraft::cend()
{
	return m_shapes.cend();
}

void Shapes::PictureDraft::AddShape(std::unique_ptr<Shape>&& shape)
{
	m_shapes.push_back(std::move(shape));
}
