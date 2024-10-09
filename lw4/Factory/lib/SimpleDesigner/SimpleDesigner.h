#pragma once
#include "../Designer/IDesigner.h"
#include "../Factory/IShapeFactory.h"
#include "../Shapes/PictureDraft.h"

namespace SimpleDesigner
{

class SimpleDesigner : public Designer::IDesigner
{
public:
	SimpleDesigner(std::unique_ptr<ShapeFactory::IShapeFactory>&& factory)
		: m_factory(std::move(factory)){};
	Shapes::PictureDraft CreateDraft(std::istream& in) override;

private:
	std::unique_ptr<ShapeFactory::IShapeFactory> m_factory;
};

} // namespace SimpleDesigner
