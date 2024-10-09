#pragma once
#include "../Shapes/PictureDraft.h"

namespace Designer
{

class IDesigner
{
public:
	virtual Shapes::PictureDraft CreateDraft(std::istream& in) = 0;
};

} // namespace Designer
