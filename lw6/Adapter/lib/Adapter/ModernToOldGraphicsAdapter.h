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
		, m_pointPos(0, 0){};

	void MoveTo(int x, int y) override
	{
		m_pointPos.x = x;
		m_pointPos.y = y;
	}

	void LineTo(int x, int y) override
	{
		m_modernRenerPtr->DrawLine(m_pointPos, modern_graphics_lib::CPoint{ x, y });
		m_pointPos.x = x;
		m_pointPos.y = y;
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer* m_modernRenerPtr;
	modern_graphics_lib::CPoint m_pointPos;
};

} // namespace Adapter
