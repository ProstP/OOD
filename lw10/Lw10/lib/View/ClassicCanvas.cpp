#include "ClassicCanvas.h"

void ClassicCanvas::DrawEllipse(Rect rect)
{
	Ellipse(m_hdc, rect.left, rect.top + m_hOffset, rect.left + rect.width, rect.top + rect.height + m_hOffset);
}

void ClassicCanvas::DrawPolygon(const std::vector<Point>& points)
{
	std::vector<POINT> figure;

	for (int i = 0; i < points.size(); i++)
	{
		figure.push_back(POINT{ points[i].x, points[i].y + m_hOffset });
	}

	Polygon(m_hdc, figure.data(), figure.size());
}
