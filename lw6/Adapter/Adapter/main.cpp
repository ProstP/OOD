#include "../lib/Adapter/ModernToOldGraphicsAdapter.h"
#include "../lib/Adapter/ModernToOldGraphicsAdapterClass.h"
#include "../lib/ModernGraphicsLib/ModernGraphicsLib.h"
#include "../lib/ShapeDrawingLib/ShapeDrawingLib.h"
#include <iostream>
#include <string>

namespace app
{

void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;
	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer render(std::cout);
	render.BeginDraw();
	Adapter::ModernToOldGraphicsAdapter adapter(render);

	shape_drawing_lib::CCanvasPainter painter(adapter);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRendererUsingClassAdapter()
{
	Adapter::ModernToOLdGraphicsAdapterClass adapter(std::cout);

	shape_drawing_lib::CCanvasPainter painter(adapter);
	PaintPicture(painter);
}

} // namespace app

int main()
{
	app::PaintPictureOnCanvas();
	std::cout << "<------->" << std::endl;
	app::PaintPictureOnModernGraphicsRenderer();
	std::cout << "<------->" << std::endl;
	app::PaintPictureOnModernGraphicsRendererUsingClassAdapter();
	/*
	std::cout << "Should we use new API (y)?" << std::endl;
	std::string userInput;

	if (std::getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}
	*/
	return 0;
}
