// Lw10.cpp : Определяет точку входа для приложения.
//

#include "Lw10.h"
#include "framework.h"
#include <sstream>
#include <string>
#include <tchar.h>
#include <vector>
#include <windows.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst; // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING]; // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING]; // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LW10, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LW10));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LW10));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LW10);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, L"Window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

struct Rect
{
	int x1;
	int y1;
	int x2;
	int y2;
};
std::vector<Rect> rects = { { 10, 20, 50, 300 }, { 100, 100, 300, 200 }, { 500, 100, 600, 200 } };
int selectedIndex = -1;
bool isDragging = false;

int offsetX = 0;
int offsetY = 0;

HBITMAP hBitMap = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int x, y, indexToDelete;

	//HDC hdcBuf = NULL;

	switch (message)
	{
	case WM_CREATE:
		//HDC hdc = GetDC(hWnd);
		//hBitMap = CreateCompatibleBitmap(hdc, 800, 900);

		//ReleaseDC(hWnd, hdc);

		break;
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		//hdcBuf = CreateCompatibleDC(hdc);

		SelectObject(hdc, hBitMap);
		/*
		std::wstringstream wss;
		wss << selectedIndex;
		std::wstring wtext = wss.str();
		LPCWSTR text = wtext.c_str();
		TextOut(hdc, 0, 0, text, wcslen(text));
		*/

		HBRUSH pbrush = CreateSolidBrush(RGB(200, 200, 200));
		SelectObject(hdc, pbrush);
		Rectangle(hdc, 10, 10, 650, 490);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		DeleteObject(pbrush);

		for (int i = 0; i < rects.size(); i++)
		{
			int r = 0;
			int g = 0;
			int b = 255;

			HBRUSH hbrush = CreateSolidBrush(RGB(r, g, b));

			SelectObject(hdc, hbrush);

			POINT triangle[3] = {
				{ (rects[i].x1 + rects[i].x2) / 2, rects[i].y1 },
				{ rects[i].x1, rects[i].y2 },
				{ rects[i].x2, rects[i].y2 }
			};
			Polygon(hdc, triangle, 3);
			//Ellipse(hdc, rects[i].x1, rects[i].y1, rects[i].x2, rects[i].y2);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			DeleteObject(hbrush);

			if (i == selectedIndex)
			{
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				SelectObject(hdc, hpen);
				Rectangle(hdc, rects[i].x1 - 1, rects[i].y1 - 1, rects[i].x2 + 1, rects[i].y2 + 1);
				SelectObject(hdc, GetStockObject(NULL_BRUSH));
				DeleteObject(hpen);
			}
		}

		//BitBlt(hdc, 0, 0, 800, 900, hdcBuf, 0, 0, SRCCOPY);
		//DeleteDC(hdcBuf);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		selectedIndex = -1;

		for (int i = 0; i < rects.size(); i++)
		{
			if (x >= rects[i].x1 && x <= rects[i].x2 && y >= rects[i].y1 && y <= rects[i].y2)
			{
				offsetX = x;
				offsetY = y;

				selectedIndex = i;
				isDragging = true;
				SetCapture(hWnd);
			}
		}
		InvalidateRect(hWnd, nullptr, TRUE);

		break;
	case WM_MOUSEMOVE:
		if (isDragging && selectedIndex != -1)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);

			int dx = x - offsetX;
			int dy = y - offsetY;

			offsetX = x;
			offsetY = y;

			rects[selectedIndex].x1 += dx;
			rects[selectedIndex].x2 += dx;
			rects[selectedIndex].y1 += dy;
			rects[selectedIndex].y2 += dy;

			InvalidateRect(hWnd, nullptr, TRUE);
		}
		break;

	case WM_LBUTTONUP:
		if (isDragging)
		{
			isDragging = false;
			ReleaseCapture();
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
