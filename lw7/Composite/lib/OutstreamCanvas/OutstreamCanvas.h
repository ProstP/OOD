#pragma once
#include "../Canvas/ICanvas.h"
#include <iomanip>

using namespace Canvas;

namespace OutstreamCanvas
{

class OutstreamCanvas : public ICanvas
{
public:
	OutstreamCanvas(std::ostream& out)
		: m_out(out){};

	void MoveTo(double x, double y) override
	{
		m_out << "Set pero to (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(double x, double y) override
	{
		m_out << "Line to (" << x << ", " << y << ")" << std::endl;
	}
	void SetOutlineColor(RGBAColor color)
	{
		uint8_t a = color;
		uint8_t b = color >> 8;
		uint8_t g = color >> 16;
		uint8_t r = color >> 24;

		m_out << "Set color to outline (#" << std::hex
			  << std::setw(2) << std::setfill('0') << static_cast<int>(r)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(g)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(b)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(a)
			  << std::dec << ")" << std::endl;
	}
	void ClearOutlineColor()
	{
		m_out << "Color of outline is cleared" << std::endl;
	}
	void SetOutlineThickness(int thickness)
	{
		m_out << "Thickness of outline is " << thickness << std::endl;
	}
	void DrawEllipse(double left, double top, double width, double height)
	{
		m_out << "Draw ellipse in fram left-top point (" << left << ", " << top << "), width - " << width << ", height - " << height << std::endl;
	}
	void BeginFill(RGBAColor color)
	{
		uint8_t a = color;
		uint8_t b = color >> 8;
		uint8_t g = color >> 16;
		uint8_t r = color >> 24;

		m_out << "Begin fill with color (#" << std::hex
			  << std::setw(2) << std::setfill('0') << static_cast<int>(r)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(g)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(b)
			  << std::setw(2) << std::setfill('0') << static_cast<int>(a)
			  << std::dec << ")" << std::endl;
	}
	void EndFill()
	{
		m_out << "End filling" << std::endl;
	}

private:
	std::ostream& m_out;
};

} // namespace OutstreamCanvas
