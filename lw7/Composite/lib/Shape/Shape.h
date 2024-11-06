#pragma once
#include "../Canvas/ICanvas.h"
#include "../CommonTypes/CommonTypes.h"
#include <iostream>
#include <optional>

using namespace CommonTypes;

namespace Shape
{

class IDrawable
{
public:
	virtual void Draw(Canvas::ICanvas& canvas) const = 0;

	virtual ~IDrawable() = default;
};

class Style
{
public:
	bool IsEnable() const
	{
		return m_enable;
	}
	void Enable(bool enable)
	{
		m_enable = enable;
	}

	std::optional<RGBAColor> GetColor()
	{
		return m_color;
	}
	void SetColor(RGBAColor color)
	{
		m_color = color;
	}

private:
	bool m_enable = false;
	std::optional<RGBAColor> m_color = std::nullopt;
};

} // namespace Shape
