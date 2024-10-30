#pragma once
#include "../GraphicsLib/GraphicsLib.h"
#include "../ModernGraphicsLib/ModernGraphicsLib.h"

namespace Adapter
{

class ModernToOLdGraphicsAdapterClass : public graphics_lib::ICanvas
	, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernToOLdGraphicsAdapterClass(std::ostream& strm)
		: CModernGraphicsRenderer(strm)
		, m_pointPos(0, 0)
	{
		BeginDraw();
	};

	void MoveTo(int x, int y) override
	{
		m_pointPos.x = x;
		m_pointPos.y = y;
	}
	void LineTo(int x, int y) override
	{
		DrawLine(m_pointPos, modern_graphics_lib::CPoint(x, y));
		m_pointPos.x = x;
		m_pointPos.y = y;
	}

private:
	modern_graphics_lib::CPoint m_pointPos;
};

} // namespace Adapter
