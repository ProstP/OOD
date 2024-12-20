#pragma once
#include "../Canvas/ICanvas.h"
#include "../Shapes/PictureDraft.h"

namespace Painter
{

class IPainter
{
public:
	virtual void DrawPicture(Shapes::PictureDraft& draft, Canvas::ICanvas& canvas) = 0;

	virtual ~IPainter() = default;
};

} // namespace Painter
