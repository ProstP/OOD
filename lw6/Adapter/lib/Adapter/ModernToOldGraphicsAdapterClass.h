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
		, m_color(0, 0, 0, 1)
	{
		BeginDraw();
	};

	void SetColor(uint32_t rgbColor) override
	{
		uint8_t b = rgbColor;
		uint8_t g = rgbColor >> 8;
		uint8_t r = rgbColor >> 16;

		m_color = modern_graphics_lib::CRGBAColor(
			static_cast<int>(r) / 255.0f,
			static_cast<int>(g) / 255.0f,
			static_cast<int>(b) / 255.0f,
			1.0f);
	}
	void MoveTo(int x, int y) override
	{
		m_pointPos.x = x;
		m_pointPos.y = y;
	}
	void LineTo(int x, int y) override
	{
		DrawLine(m_pointPos, modern_graphics_lib::CPoint(x, y), m_color);
		m_pointPos.x = x;
		m_pointPos.y = y;
	}

private:
	modern_graphics_lib::CPoint m_pointPos;
	modern_graphics_lib::CRGBAColor m_color;
};

} // namespace Adapter
