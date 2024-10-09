#include "Painter.h"

void SimplePainter::SimplePainter::DrawPicture(const Shapes::PictureDraft& draft, Canvas::ICanvas& canvas)
{
	for (int i = 0; i < draft.GetShapeCount(); i++)
	{
		draft.GetShape(i)->Draw(canvas);
	}
}
