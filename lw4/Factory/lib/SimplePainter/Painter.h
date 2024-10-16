#pragma once
#include "../Painter/IPainter.h"

namespace SimplePainter
{

class SimplePainter : public Painter::IPainter
{
public:
	void DrawPicture(Shapes::PictureDraft& draft, Canvas::ICanvas& canvas) override;

	~SimplePainter() override = default;
};

} // namespace SimplePainter
