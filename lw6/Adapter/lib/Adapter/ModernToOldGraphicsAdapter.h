#pragma once
#include "../GraphicsLib/GraphicsLib.h"
#include "../ModernGraphicsLib/ModernGraphicsLib.h"

namespace Adapter
{

class ModernToOldGraphicsAdapter : public graphics_lib::ICanvas
{
public:
	ModernToOldGraphicsAdapter(modern_graphics_lib::CModernGraphicsRenderer& render)
		: m_modernRenerPtr(&render)
		, m_startPoint(0, 0)
	{
		m_modernRenerPtr->BeginDraw();
	};

	void MoveTo(int x, int y) override
	{
		m_startPoint.x = x;
		m_startPoint.y = y;
	}

	void LineTo(int x, int y) override
	{
		m_modernRenerPtr->DrawLine(m_startPoint, modern_graphics_lib::CPoint{ x, y });
		m_startPoint.x = x;
		m_startPoint.y = y;
	}

	~ModernToOldGraphicsAdapter()
	{
		m_modernRenerPtr->EndDraw();
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer* m_modernRenerPtr;
	modern_graphics_lib::CPoint m_startPoint;
};

} // namespace Adapter
