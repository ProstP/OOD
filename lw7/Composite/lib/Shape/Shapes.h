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
	virtual std::shared_ptr<IShape> GetParent() = 0;

	virtual ~IShape() = default;
};

class Group : public IShape
{
public:
	Group(std::shared_ptr<IShape> parent)
		: m_parent(parent){};
	size_t GetShapeCount() const
	{
		return m_shapes.size();
	}
	void InsertShape(std::shared_ptr<IShape> shape, size_t pos)
	{
		if (pos > m_shapes.size())
		{
			throw std::out_of_range("Out of range in inserting shape");
		}

		RectD shapeFrame = shape->GetFrame();

		if (shapeFrame.left < m_groupFrame.left)
		{
			double endX = m_groupFrame.left + m_groupFrame.width;

			m_groupFrame.left = shapeFrame.left;
			m_groupFrame.width = endX - m_groupFrame.left;
		}
		if (shapeFrame.top < m_groupFrame.top)
		{
			double endY = m_groupFrame.top + m_groupFrame.height;

			m_groupFrame.top = shapeFrame.top;
			m_groupFrame.height = endY - m_groupFrame.top;
		}
		if (shapeFrame.left + shapeFrame.width > m_groupFrame.left + m_groupFrame.width)
		{
			m_groupFrame.width = shapeFrame.left + shapeFrame.width - m_groupFrame.left;
		}
		if (shapeFrame.top + shapeFrame.height > m_groupFrame.top + m_groupFrame.height)
		{
			m_groupFrame.height = shapeFrame.top + shapeFrame.height - m_groupFrame.top;
		}

		if (m_shapes.empty())
		{
			m_shapes.push_back(shape);
			return;
		}
		else if (pos == m_shapes.size())
		{
			m_shapes.push_back(shape);
			return;
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
		return m_groupFrame;
	}
	void SetFrame(RectD rect) override
	{
		for (auto& shape : m_shapes)
		{
			RectD shapeRect = shape->GetFrame();

			double startX = shapeRect.left - m_groupFrame.left;
			double endX = startX + shapeRect.width;

			double newStartX = (startX / m_groupFrame.width) * rect.width;
			double newEndX = (endX / m_groupFrame.width) * rect.width;

			shapeRect.width = newEndX - newStartX;
			shapeRect.left = newStartX - rect.left;

			double startY = shapeRect.top - m_groupFrame.top;
			double endY = startY + shapeRect.height;

			double newStartY = (startY / m_groupFrame.height) * rect.height;
			double newEndY = (endY / m_groupFrame.height) * rect.height;

			shapeRect.height = newEndY - newStartY;
			shapeRect.top = newStartY - rect.top;

			shape->SetFrame(shapeRect);
		}

		m_groupFrame = rect;
	}

	StyleWithThickness GetOutlineStyle() const override
	{
		if (m_shapes.size() == 0)
		{
			return StyleWithThickness();
		}
		StyleWithThickness style = m_shapes[0]->GetOutlineStyle();
		for (int i = 1; i < m_shapes.size(); i++)
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
		for (int i = 0; i < m_shapes.size(); i++)
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
		for (int i = 1; i < m_shapes.size(); i++)
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
		for (int i = 0; i < m_shapes.size(); i++)
		{
			m_shapes[i]->SetFillStyle(style);
		}
	}

	Group* GetGroup() override
	{
		return this;
	}
	std::shared_ptr<IShape> GetParent() override
	{
		return m_parent;
	}

	void Draw(Canvas::ICanvas& canvas) const override
	{
		for (int i = 0; i <= m_shapes.size(); i++)
		{
			m_shapes[i]->Draw(canvas);
		}
	}

private:
	std::shared_ptr<IShape> m_parent;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	RectD m_groupFrame = { 0, 0, 0, 0 };
};

class Shape : public IShape
{
public:
	Shape(std::shared_ptr<IShape> parent)
		: m_frame({ 0, 0, 0, 0 })
		, m_parent(parent){};
	RectD GetFrame() const override
	{
		return m_frame;
	}
	void SetFrame(RectD rect) override
	{
		m_frame = rect;
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
	std::shared_ptr<IShape> GetParent() override
	{
		return m_parent;
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
	RectD m_frame;
	StyleWithThickness m_outlineStyle;
	Style m_fillStyle;
	std::shared_ptr<IShape> m_parent;
};

class Slide
{
public:
	Slide(double width, double height)
	{
		RectD rect{ 0.0, 0.0, 0, 0 };
		m_shapes = std::make_shared<Group>(nullptr);
		m_shapes->SetFrame(rect);
	}
	std::shared_ptr<Group> GetShapes()
	{
		return m_shapes;
	}
	void DrawBackground(Canvas::ICanvas& canvas)
	{
		canvas.BeginFill(m_backgroundColor);

		RectD rect = m_shapes->GetFrame();
		canvas.MoveTo(0, 0);
		canvas.LineTo(m_width, 0);
		canvas.LineTo(m_width, m_height);
		canvas.LineTo(0, m_height);
		canvas.LineTo(0, 0);

		canvas.EndFill();
	}
	void SetBackgroundColor(RGBAColor color)
	{
		m_backgroundColor = color;
	}

private:
	double m_width;
	double m_height;
	std::shared_ptr<Group> m_shapes;
	RGBAColor m_backgroundColor;
};

} // namespace Shapes
