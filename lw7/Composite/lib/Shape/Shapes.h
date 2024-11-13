#pragma once
#include "../Canvas/ICanvas.h"
#include "../CommonTypes/CommonTypes.h"
#include <functional>
#include <iostream>
#include <limits>
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
	int m_thickness = 0;
};

class GroupStyle : public IStyle
{
public:
	GroupStyle(std::function<std::vector<std::shared_ptr<IStyle>>()> getStylesFn,
		std::function<void(std::optional<bool>, std::optional<RGBAColor>)> editStylesFn)
		: m_getStylesFn(getStylesFn)
		, m_editStylesFn(editStylesFn)
	{
	}

	bool IsEnable() const override
	{
		std::vector<std::shared_ptr<IStyle>> styles = m_getStylesFn();
		CheckStylesToEmpty(styles);

		auto enable = styles[0]->IsEnable();

		for (size_t i = 1; i < styles.size(); i++)
		{
			if (enable != styles[i]->IsEnable())
			{
				return false;
			}
		}

		return enable;
	}
	void Enable(bool enable) override
	{
		m_editStylesFn(enable, std::nullopt);
	}

	std::optional<RGBAColor> GetColor() const override
	{
		std::vector<std::shared_ptr<IStyle>> styles = m_getStylesFn();
		CheckStylesToEmpty(styles);

		auto color = styles[0]->GetColor();

		for (size_t i = 1; i < styles.size(); i++)
		{
			if (color != styles[i]->GetColor())
			{
				return std::nullopt;
			}
		}

		return color;
	}
	void SetColor(RGBAColor color) override
	{
		m_editStylesFn(std::nullopt, color);
	}

private:
	std::function<std::vector<std::shared_ptr<IStyle>>()> m_getStylesFn;
	std::function<void(std::optional<bool>, std::optional<RGBAColor>)> m_editStylesFn;
	void CheckStylesToEmpty(std::vector<std::shared_ptr<IStyle>> styles) const
	{
		if (styles.empty())
		{
			throw std::invalid_argument("Style withut childs");
		}
	}
};

class GroupStyleWithThicness : public IStyleWithThickness
{
public:
	GroupStyleWithThicness(std::function<std::vector<std::shared_ptr<IStyleWithThickness>>()> getStylesFn,
		std::function<void(std::optional<bool>, std::optional<RGBAColor>, std::optional<int>)> editStylesFn)
		: m_getStylesFn(getStylesFn)
		, m_editStylesFn(editStylesFn)
	{
	}
	bool IsEnable() const override
	{
		std::vector<std::shared_ptr<IStyleWithThickness>> styles = m_getStylesFn();
		CheckStylesToEmpty(styles);

		auto enable = styles[0]->IsEnable();

		for (size_t i = 1; i < styles.size(); i++)
		{
			if (enable != styles[i]->IsEnable())
			{
				return false;
			}
		}

		return enable;
	}
	void Enable(bool enable) override
	{
		m_editStylesFn(enable, std::nullopt, std::nullopt);
	}

	std::optional<RGBAColor> GetColor() const override
	{
		std::vector<std::shared_ptr<IStyleWithThickness>> styles = m_getStylesFn();
		CheckStylesToEmpty(styles);

		auto color = styles[0]->GetColor();

		for (size_t i = 1; i < styles.size(); i++)
		{
			if (color != styles[i]->GetColor())
			{
				return std::nullopt;
			}
		}

		return color;
	}
	void SetColor(RGBAColor color) override
	{
		m_editStylesFn(std::nullopt, color, std::nullopt);
	}

	int GetThickness() const override
	{
		std::vector<std::shared_ptr<IStyleWithThickness>> styles = m_getStylesFn();
		CheckStylesToEmpty(styles);

		auto thickness = styles[0]->GetThickness();

		for (size_t i = 1; i < styles.size(); i++)
		{
			if (thickness != styles[i]->GetThickness())
			{
				return 0;
			}
		}

		return thickness;
	}
	void SetThickness(int thickness) override
	{
		m_editStylesFn(std::nullopt, std::nullopt, thickness);
	}

private:
	std::function<std::vector<std::shared_ptr<IStyleWithThickness>>()> m_getStylesFn;
	std::function<void(std::optional<bool>, std::optional<RGBAColor>, std::optional<int>)> m_editStylesFn;
	void CheckStylesToEmpty(std::vector<std::shared_ptr<IStyleWithThickness>> styles) const
	{
		if (styles.empty())
		{
			throw std::invalid_argument("Style withut childs");
		}
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
		double minLeft = std::numeric_limits<double>::max();
		double minTop = std::numeric_limits<double>::max();
		double maxWidth = 0;
		double maxHeight = 0;

		for (int i = 0; i < m_shapes.size(); i++)
		{
			auto shapeFrame = m_shapes[i]->GetFrame();

			if (shapeFrame.width == 0 && shapeFrame.height == 0)
			{
				continue;
			}

			if (minLeft == std::numeric_limits<double>::max())
			{
				minLeft = shapeFrame.left;
			}
			if (shapeFrame.left < minLeft)
			{
				double endX = minLeft + maxWidth;

				minLeft = shapeFrame.left;
				maxWidth = endX - minLeft;
			}
			if (minTop == std::numeric_limits<double>::max())
			{
				minTop = shapeFrame.top;
			}
			if (shapeFrame.top < minTop)
			{
				double endY = minTop + maxHeight;

				minTop = shapeFrame.top;
				maxHeight = endY - minTop;
			}
			if (shapeFrame.left + shapeFrame.width > minLeft + maxWidth)
			{
				maxWidth = shapeFrame.left + shapeFrame.width - minLeft;
			}
			if (shapeFrame.top + shapeFrame.height > minTop + maxHeight)
			{
				maxHeight = shapeFrame.top + shapeFrame.height - minTop;
			}
		}

		minLeft = minLeft == std::numeric_limits<double>::max() ? 0 : minLeft;
		minTop = minTop == std::numeric_limits<double>::max() ? 0 : minTop;

		return RectD{ minLeft, minTop, maxWidth, maxHeight };
	}
	void SetFrame(RectD rect) override
	{
		RectD groupFrame = GetFrame();

		for (auto& shape : m_shapes)
		{
			RectD shapeRect = shape->GetFrame();

			double startX = shapeRect.left - groupFrame.left;
			double endX = startX + shapeRect.width;

			double newStartX = (startX / groupFrame.width) * rect.width;
			double newEndX = (endX / groupFrame.width) * rect.width;

			shapeRect.width = newEndX - newStartX;
			shapeRect.left = newStartX + rect.left;

			double startY = shapeRect.top - groupFrame.top;
			double endY = startY + shapeRect.height;

			double newStartY = (startY / groupFrame.height) * rect.height;
			double newEndY = (endY / groupFrame.height) * rect.height;

			shapeRect.height = newEndY - newStartY;
			shapeRect.top = newStartY + rect.top;

			shape->SetFrame(shapeRect);
		}
	}

	std::shared_ptr<IStyleWithThickness> GetOutlineStyle() const override
	{
		const std::vector<std::shared_ptr<IShape>>* shapesPtr = &m_shapes;
		auto getFn = [shapesPtr]() {
			std::vector<std::shared_ptr<IStyleWithThickness>> styles;

			for (int i = 0; i < shapesPtr->size(); i++)
			{
				styles.push_back(shapesPtr->at(i)->GetOutlineStyle());
			}

			return styles;
		};
		auto editFn = [shapesPtr](std::optional<bool> enable, std::optional<RGBAColor> color, std::optional<int> thickness) {
			for (int i = 0; i < shapesPtr->size(); i++)
			{
				if (enable != std::nullopt)
				{
					shapesPtr->at(i)->GetOutlineStyle()->Enable(enable.value());
				}
				if (color != std::nullopt)
				{
					shapesPtr->at(i)->GetOutlineStyle()->SetColor(color.value());
				}
				if (thickness != std::nullopt)
				{
					shapesPtr->at(i)->GetOutlineStyle()->SetThickness(thickness.value());
				}
			}
		};
		GroupStyleWithThicness groupStyle(getFn, editFn);

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
		const std::vector<std::shared_ptr<IShape>>* shapesPtr = &m_shapes;
		auto getFn = [shapesPtr]() {
			std::vector<std::shared_ptr<IStyle>> styles;

			for (int i = 0; i < shapesPtr->size(); i++)
			{
				styles.push_back(shapesPtr->at(i)->GetFillStyle());
			}

			return styles;
		};
		auto setFn = [shapesPtr](std::optional<bool> enable, std::optional<RGBAColor> color) {
			for (int i = 0; i < shapesPtr->size(); i++)
			{
				if (enable != std::nullopt)
				{
					shapesPtr->at(i)->GetFillStyle()->Enable(enable.value());
				}
				if (color != std::nullopt)
				{
					shapesPtr->at(i)->GetFillStyle()->SetColor(color.value());
				}
			}
		};

		GroupStyle style(getFn, setFn);

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
