#pragma once
#include "../Canvas/ICanvas.h"
#include "../Types/Types.h"

namespace Shapes
{

class Shape
{
public:
	void SetRect(Types::Rect rect);
	Types::Rect GetRect() const;

	void Move(int dx, int dy);
	void Resize(int width, int height);

	void Draw(Canvas::ICanvas& canvas) const;

	virtual ~Shape() = default;

protected:
	virtual void DrawImp(Canvas::ICanvas& canvas) const = 0;

private:
	Types::Rect m_rect;
};

} // namespace Shapes
