#pragma once
#include "../Canvas/ICanvas.h"
#include "../CommonTypes/CommonTypes.h"
#include <iostream>
#include <optional>
#include <vector>

using namespace CommonTypes;

namespace Shapes
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

	bool operator==(Style style)
	{
		return (this->IsEnable() == style.IsEnable() && this->GetColor() == style.GetColor());
	}
	bool operator!=(Style style)
	{
		return !(*this == style);
	}

private:
	bool m_enable = false;
	std::optional<RGBAColor> m_color = std::nullopt;
};

class Group;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(RectD rect) = 0;

	virtual Style GetOutlineStyle() const = 0;
	virtual void SetOutlineStyle(Style style) = 0;

	virtual Style GetFillStyle() const = 0;
	virtual void SetFillStyle(Style style) = 0;

	virtual Group* GetGroup() = 0;

	virtual ~IShape() = default;
};

class Group : public IShape
{
public:
	size_t GetShapeCount() const
	{
		return m_shapes.size();
	}
	void InserShape(std::shared_ptr<IShape> shape, size_t pos)
	{
		if (pos >= m_shapes.size())
		{
			throw std::out_of_range("Out of range in inserting shape");
		}

		m_shapes.insert(m_shapes.begin() + pos, shape);
	}
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index)
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Out of range in getting shape");
		}

		return m_shapes[index];
	}
	void RemoveShapeAtIndex(size_t index)
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Out of range in removing shape");
		}

		m_shapes.erase(m_shapes.begin() + index);
	}

	RectD GetFrame() const override;
	void SetFrame(RectD rect) override
	{
	}

	Style GetOutlineStyle() const override
	{
		if (m_shapes.size() == 0)
		{
			return Style();
		}
		Style style = m_shapes[0]->GetOutlineStyle();
		for (int i = 1; m_shapes.size(); i++)
		{
			if (style != m_shapes[i]->GetOutlineStyle())
			{
				return Style();
			}
		}

		return style;
	}
	void SetOutlineStyle(Style style) override
	{
		for (int i = 0; i <= m_shapes.size(); i++)
		{
			m_shapes[i]->SetOutlineStyle(style);
		}
	}

	Style GetFillStyle() const override
	{
		if (m_shapes.size() == 0)
		{
			return Style();
		}
		Style style = m_shapes[0]->GetFillStyle();
		for (int i = 1; m_shapes.size(); i++)
		{
			if (style != m_shapes[i]->GetFillStyle())
			{
				return Style();
			}
		}

		return style;
	}
	void SetFillStyle(Style style) override
	{
		for (int i = 0; i <= m_shapes.size(); i++)
		{
			m_shapes[i]->SetFillStyle(style);
		}
	}

	Group* GetGroup() override
	{
		return this;
	}

	void Draw(Canvas::ICanvas& canvas) const override
	{
		for (int i = 0; i <= m_shapes.size(); i++)
		{
			m_shapes[i]->Draw(canvas);
		}
	}

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

class Shape : public IShape
{
public:
	RectD GetFrame() const override
	{
		return m_rect;
	}
	void SetFrame(RectD rect) override
	{
		m_rect = rect;
	}

	Style GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}
	void SetOutlineStyle(Style style) override
	{
		m_outlineStyle = style;
	}

	Style GetFillStyle() const override
	{
		return m_fillStyle;
	}
	void SetFillStyle(Style style) override
	{
		m_fillStyle = style;
	}

	virtual ~Shape() = default;

protected:
	RectD m_rect;
	Style m_outlineStyle;
	Style m_fillStyle;
};

} // namespace Shapes
