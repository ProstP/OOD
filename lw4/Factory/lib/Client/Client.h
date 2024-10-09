#pragma once
#include "../Canvas/ICanvas.h"
#include "../Designer/IDesigner.h"
#include "../Painter/IPainter.h"
#include <memory>

namespace Client
{

class Client
{
public:
	Client(std::unique_ptr<Canvas::ICanvas>&& canvas,
		std::unique_ptr<Designer::IDesigner>&& designer,
		std::unique_ptr<Painter::IPainter>&& painter)
		: m_canvas(std::move(canvas))
		, m_designer(std::move(designer))
		, m_painter(std::move(painter)){};

	void Run(std::istream& in, std::ostream& out);

private:
	std::unique_ptr<Canvas::ICanvas> m_canvas;
	std::unique_ptr<Designer::IDesigner> m_designer;
	std::unique_ptr<Painter::IPainter> m_painter;
};

} // namespace Client
