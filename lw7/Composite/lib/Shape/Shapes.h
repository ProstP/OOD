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

	std::optional<RGBAColor> GetColor() const
	{
		return m_color;
	}
	void SetColor(RGBAColor color)
	{
		m_color = color;
	}

	virtual bool operator==(Style style)
	{
		return (this->IsEnable() == style.IsEnable() && this->GetColor() == style.GetColor());
	}
	virtual bool operator!=(Style style)
	{
		return !(*this == style);
	}

private:
	bool m_enable = false;
	std::optional<RGBAColor> m_color = std::nullopt;
};

class StyleWithThickness : public Style
{
public:
	int GetThickness() const
	{
		return m_thickness;
	}
	void SetThickness(int thickness)
	{
		m_thickness = thickness;
	}

private:
	int m_thickness = 1;
};

class Group;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(RectD rect) = 0;

	virtual StyleWithThickness GetOutlineStyle() const = 0;
	virtual void SetOutlineStyle(StyleWithThickness style) = 0;

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
		if (m_shapes.empty())
		{
			m_shapes.push_back(shape);
		}

		if (pos >= m_shapes.size())
		{
			throw std::out_of_range("Out of range in inserting shape");
		}

		RectD shapeRect = shape->GetFrame();

		if (shapeRect.left < m_groupRect.left)
		{
			m_groupRect.left = shapeRect.left;
		}
		if (shapeRect.top < m_groupRect.top)
		{
			m_groupRect.top = shapeRect.top;
		}
		if (shapeRect.left + shapeRect.width > m_groupRect.left + m_groupRect.width)
		{
			m_groupRect.width = shapeRect.left + shapeRect.width - m_groupRect.left;
		}
		if (shapeRect.top + shapeRect.height > m_groupRect.top + m_groupRect.height)
		{
			m_groupRect.height = shapeRect.top + shapeRect.height - m_groupRect.top;
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

	RectD GetFrame() const override
	{
		return m_groupRect;
	}
	void SetFrame(RectD rect) override
	{
		for (auto& shape : m_shapes)
		{
			RectD shapeRect = shape->GetFrame();

			double startX = shapeRect.left - m_groupRect.left;
			double endX = startX + shapeRect.width;

			double newStartX = (startX / m_groupRect.width) * rect.width;
			double newEndX = (endX / m_groupRect.width) * rect.width;

			shapeRect.width = newEndX - newStartX;
			shapeRect.left = newStartX - rect.left;

			double startY = shapeRect.top - m_groupRect.top;
			double endY = startY + shapeRect.height;

			double newStartY = (startY / m_groupRect.height) * rect.height;
			double newEndY = (endY / m_groupRect.height) * rect.height;

			shapeRect.height = newEndY - newStartY;
			shapeRect.top = newStartY - rect.top;

			shape->SetFrame(shapeRect);
		}

		m_groupRect = rect;
	}

	StyleWithThickness GetOutlineStyle() const override
	{
		if (m_shapes.size() == 0)
		{
			return StyleWithThickness();
		}
		StyleWithThickness style = m_shapes[0]->GetOutlineStyle();
		for (int i = 1; m_shapes.size(); i++)
		{
			if (style != m_shapes[i]->GetOutlineStyle())
			{
				return StyleWithThickness();
			}
		}

		return style;
	}
	void SetOutlineStyle(StyleWithThickness style) override
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
	RectD m_groupRect = { 0, 0, 0, 0 };
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

	StyleWithThickness GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}
	void SetOutlineStyle(StyleWithThickness style) override
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

	Group* GetGroup() override
	{
		return nullptr;
	}

	void Draw(Canvas::ICanvas& canvas) const final override
	{
		if (!m_fillStyle.IsEnable() && !m_outlineStyle.IsEnable())
		{
			throw std::invalid_argument("Shape is invisible");
		}

		if (m_fillStyle.IsEnable())
		{
			std::optional<RGBAColor> color = m_fillStyle.GetColor();
			if (color == std::nullopt)
			{
				canvas.BeginFill(0x00000000);
			}
			else
			{
				canvas.BeginFill(color.value());
			}
		}
		if (m_outlineStyle.IsEnable())
		{
			std::optional<RGBAColor> color = m_outlineStyle.GetColor();
			if (color == std::nullopt)
			{
				canvas.SetOutlineColor(0x00000000);
			}
			else
			{
				canvas.SetOutlineColor(color.value());
			}
			canvas.SetOutlineThickness(m_outlineStyle.GetThickness());
		}

		DrawImp(canvas);

		canvas.ClearOutlineColor();
		canvas.EndFill();
	}

	virtual ~Shape() = default;

protected:
	virtual void DrawImp(Canvas::ICanvas& canvas) const = 0;

private:
	RectD m_rect;
	StyleWithThickness m_outlineStyle;
	Style m_fillStyle;
};

class Slide
{
public:
	Slide()
	{
		m_shapes = std::make_shared<Group>();
	}
	std::shared_ptr<Group> GetShapes()
	{
		return m_shapes;
	}
	void DrawBackground(Canvas::ICanvas& canvas)
	{
		canvas.BeginFill(m_backgroundColor);

		RectD rect = m_shapes->GetFrame();
		canvas.MoveTo(rect.left, rect.top);
		canvas.LineTo(rect.left + rect.width, rect.top);
		canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
		canvas.LineTo(rect.left, rect.top + rect.height);
		canvas.LineTo(rect.left, rect.top);

		canvas.EndFill();
	}
	void SetBackgroundColor(RGBAColor color)
	{
		m_backgroundColor = color;
	}

private:
	std::shared_ptr<Group> m_shapes;
	RGBAColor m_backgroundColor;
};

} // namespace Shapes
