#include "Painter.h"

void SimplePainter::SimplePainter::DrawPicture(Shapes::PictureDraft& draft, Canvas::ICanvas& canvas)
{
	for (auto shape = draft.begin(); shape != draft.end(); shape++)
	{
		shape->get()->Draw(canvas);
	}
}
