// Lw10.cpp : Определяет точку входа для приложения.
//

#include "Lw10.h"
#include "../lib/Model/ShapeStore.h"
#include "../lib/SimpleShapeFactory/ShapeFactory.h"
#include "../lib/View/View.h"
#include <windows.h>

using namespace Model;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SimpleShapeFactory::ShapeFactory factory;
	ShapeStore store(factory);
	View view(hInstance, nCmdShow, store);

	view.Run();
}
