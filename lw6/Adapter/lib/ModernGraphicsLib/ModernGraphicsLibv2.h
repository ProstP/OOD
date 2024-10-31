#pragma once
#include "ModernGraphicsLib.h"

namespace modern_graphics_lib_v2
{

class ModernGraphicsRenderv2 : public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsRenderv2(std::ostream& out)
		: CModernGraphicsRenderer(out){};

	void BeginDraw() override
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}
		m_out << "<new draw>" << std::endl;
		m_drawing = true;
	}
	void EndDraw() override
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</new draw>" << std::endl;
		m_drawing = false;
	}

	~ModernGraphicsRenderv2()
	{
		if (m_drawing)
		{
			EndDraw();
		}
	}
};

} // namespace modern_graphics_lib_v2
