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

class IStyle
{
public:
	virtual bool IsEnable() const = 0;
	virtual void Enable(bool enable) = 0;
	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	~IStyle() = default;
};

class IStyleWithThickness : public IStyle
{
public:
	virtual int GetThickness() const = 0;
	virtual void SetThickness(int thickness) = 0;

	~IStyleWithThickness() = default;
};

class Style : public IStyle
{
public:
	bool IsEnable() const override
	{
		return m_enable;
	}
	void Enable(bool enable) override
	{
		m_enable = enable;
	}

	std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}
	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

private:
	bool m_enable = false;
	std::optional<RGBAColor> m_color = std::nullopt;
};

class StyleWithThickness : public IStyleWithThickness
{
public:
	bool IsEnable() const override
	{
		return m_enable;
	}
	void Enable(bool enable) override
	{
		m_enable = enable;
	}

	std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}
	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

	int GetThickness() const override
	{
		return m_thickness;
	}
	void SetThickness(int thickness) override
	{
		m_thickness = thickness;
	}

private:
	bool m_enable = false;
	std::optional<RGBAColor> m_color = std::nullopt;
	int m_thickness = 1;
};

class GroupStyle : public IStyle
{
public:
	void AddStyle(std::shared_ptr<IStyle> style)
	{
		m_styles.push_back(style);
	};

	bool IsEnable() const override
	{
		CheckStylesToEmpty();

		if (CheckStyleToEqualEachOther())
		{
			return m_styles[0]->IsEnable();
		}
		else
		{
			return false;
		}
	}
	void Enable(bool enable) override
	{
		CheckStylesToEmpty();

		for (int i = 0; i < m_styles.size(); i++)
		{
			m_styles[i]->Enable(enable);
		}
	}

	std::optional<RGBAColor> GetColor() const override
	{
		CheckStylesToEmpty();

		if (CheckStyleToEqualEachOther())
		{
			return m_styles[0]->GetColor();
		}
		else
		{
			return std::nullopt;
		}
	}
	void SetColor(RGBAColor color) override
	{
		CheckStylesToEmpty();

		for (int i = 0; i < m_styles.size(); i++)
		{
			m_styles[i]->SetColor(color);
		}
	}

private:
	std::vector<std::shared_ptr<IStyle>> m_styles;
	void CheckStylesToEmpty() const
	{
		if (m_styles.empty())
		{
			throw std::invalid_argument("Style withut childs");
		}
	}
	bool CheckStyleToEqualEachOther() const
	{
		CheckStylesToEmpty();

		for (size_t i = 1; i < m_styles.size(); i++)
		{
			if (m_styles[i - 1]->IsEnable() != m_styles[i]->IsEnable()
				|| m_styles[i - 1]->GetColor() != m_styles[i]->GetColor())
			{
				return false;
			}
		}

		return true;
	}
};

class GroupStyleWithThicness : public IStyleWithThickness
{
public:
	void AddStyle(std::shared_ptr<IStyleWithThickness> style)
	{
		m_styles.push_back(style);
	};

	bool IsEnable() const override
	{
		CheckStylesToEmpty();

		if (CheckStyleToEqualEachOther())
		{
			return m_styles[0]->IsEnable();
		}
		else
		{
			return false;
		}
	}
	void Enable(bool enable) override
	{
		CheckStylesToEmpty();

		for (int i = 0; i < m_styles.size(); i++)
		{
			m_styles[i]->Enable(enable);
		}
	}

	std::optional<RGBAColor> GetColor() const override
	{
		CheckStylesToEmpty();

		if (CheckStyleToEqualEachOther())
		{
			return m_styles[0]->GetColor();
		}
		else
		{
			return std::nullopt;
		}
	}
	void SetColor(RGBAColor color) override
	{
		CheckStylesToEmpty();

		for (int i = 0; i < m_styles.size(); i++)
		{
			m_styles[i]->SetColor(color);
		}
	}

	int GetThickness() const override
	{
		CheckStylesToEmpty();

		if (CheckStyleToEqualEachOther())
		{
			return m_styles[0]->GetThickness();
		}
		else
		{
			return 0;
		}
	}
	void SetThickness(int thickness) override
	{
		CheckStylesToEmpty();

		for (int i = 0; i < m_styles.size(); i++)
		{
			m_styles[i]->SetThickness(thickness);
		}
	}

private:
	std::vector<std::shared_ptr<IStyleWithThickness>> m_styles;
	void CheckStylesToEmpty() const
	{
		if (m_styles.empty())
		{
			throw std::invalid_argument("Style withut childs");
		}
	}
	bool CheckStyleToEqualEachOther() const
	{
		CheckStylesToEmpty();

		for (size_t i = 1; i < m_styles.size(); i++)
		{
			if (m_styles[i - 1]->IsEnable() != m_styles[i]->IsEnable()
				|| m_styles[i - 1]->GetColor() != m_styles[i]->GetColor()
				|| m_styles[i - 1]->GetThickness() != m_styles[i]->GetThickness())
			{
				return false;
			}
		}

		return true;
	}
};

class Group;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(RectD rect) = 0;

	virtual std::shared_ptr<IStyleWithThickness> GetOutlineStyle() const = 0;
	virtual void SetOutlineStyle(std::shared_ptr<IStyleWithThickness> style) = 0;

	virtual std::shared_ptr<IStyle> GetFillStyle() const = 0;
	virtual void SetFillStyle(std::shared_ptr<IStyle> style) = 0;

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

	std::shared_ptr<IStyleWithThickness> GetOutlineStyle() const override
	{
		if (m_shapes.size() == 0)
		{
			return nullptr;
		}
		GroupStyleWithThicness groupStyle;

		for (int i = 1; i < m_shapes.size(); i++)
		{
			groupStyle.AddStyle(m_shapes[i]->GetOutlineStyle());
		}

		return std::make_shared<GroupStyleWithThicness>(groupStyle);
	}
	void SetOutlineStyle(std::shared_ptr<IStyleWithThickness> style) override
	{
		for (int i = 0; i < m_shapes.size(); i++)
		{
			m_shapes[i]->SetOutlineStyle(style);
		}
	}

	std::shared_ptr<IStyle> GetFillStyle() const override
	{
		if (m_shapes.size() == 0)
		{
			return nullptr;
		}
		GroupStyle style;

		for (int i = 1; i < m_shapes.size(); i++)
		{
			style.AddStyle(m_shapes[i]->GetFillStyle());
		}

		return std::make_shared<GroupStyle>(style);
	}
	void SetFillStyle(std::shared_ptr<IStyle> style) override
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

	std::shared_ptr<IStyleWithThickness> GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}
	void SetOutlineStyle(std::shared_ptr<IStyleWithThickness> style) override
	{
		m_outlineStyle = style;
	}

	std::shared_ptr<IStyle> GetFillStyle() const override
	{
		return m_fillStyle;
	}
	void SetFillStyle(std::shared_ptr<IStyle> style) override
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
		if (!m_fillStyle->IsEnable() && !m_outlineStyle->IsEnable())
		{
			throw std::invalid_argument("Shape is invisible");
		}

		if (m_fillStyle->IsEnable())
		{
			std::optional<RGBAColor> color = m_fillStyle->GetColor();
			if (color == std::nullopt)
			{
				canvas.BeginFill(0x00000000);
			}
			else
			{
				canvas.BeginFill(color.value());
			}
		}
		if (m_outlineStyle->IsEnable())
		{
			std::optional<RGBAColor> color = m_outlineStyle->GetColor();
			if (color == std::nullopt)
			{
				canvas.SetOutlineColor(0x00000000);
			}
			else
			{
				canvas.SetOutlineColor(color.value());
			}
			canvas.SetOutlineThickness(m_outlineStyle->GetThickness());
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
	std::shared_ptr<IStyleWithThickness> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
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
