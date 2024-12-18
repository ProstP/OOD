#pragma once
#include "../Canvas/ICanvas.h"
#include <windows.h>

using namespace Types;

class ClassicCanvas : public Canvas::ICanvas
{
public:
	ClassicCanvas(HDC hdc, int hOffset = 0)
		: m_hdc(hdc)
		, m_hOffset(hOffset){};

	void DrawEllipse(Rect rect) override;
	void DrawPolygon(const std::vector<Point>& points) override;

private:
	HDC m_hdc;
	int m_hOffset;
};
