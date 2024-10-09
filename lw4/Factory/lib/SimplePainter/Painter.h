#pragma once
#include "../Painter/IPainter.h"

namespace SimplePainter
{

class SimplePainter : public Painter::IPainter
{
public:
	void DrawPicture(const Shapes::PictureDraft& draft, Canvas::ICanvas& canvas) override;
};

} // namespace SimplePainter
