#pragma once
#include "../../Lw10/Resource.h"
#include "../Model/ShapeStore.h"
#include "../Types/Types.h"
#include "Controller.h"
#include <iostream>
#include <vector>
#include <windows.h>

using namespace Types;

class View
{
public:
	View(HINSTANCE hInstance, int nCmdShow, Model::ShapeStore& store)
		: m_hInstance(hInstance)
		, m_store(store)
		, m_controller(store)
	{
		RegistWindow();
		InitInstance(nCmdShow);
	}

	void Run()
	{
		HACCEL hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_LW10));
		MSG msg;

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

private:
	Rect m_canvasRect = { 640, 480 };
	HINSTANCE m_hInstance;
	Model::ShapeStore& m_store;
	Controller m_controller;

	void RegistWindow()
	{
		WNDCLASSEXW wcex = { 0 };

		wcex.cbSize = sizeof(WNDCLASSEXW);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = &View::WndProc;
		wcex.hInstance = m_hInstance;
		wcex.lpszClassName = L"MyWindowClass";

		RegisterClassExW(&wcex);
	}
	void InitInstance(int nCmdShow)
	{
		HWND hWnd = CreateWindowW(L"MyWindowClass", L"Window", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, this);

		if (!hWnd)
		{
			throw std::logic_error("Error in create window");
		}

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CREATE:

			break;
		case WM_COMMAND: {
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
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

			HBRUSH pbrush = CreateSolidBrush(RGB(200, 200, 200));
			SelectObject(hdc, pbrush);
			Rectangle(hdc, 10, 10, 650, 490);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			DeleteObject(pbrush);

			EndPaint(hWnd, &ps);
		}
		break;
		case WM_LBUTTONDOWN:

			break;
		case WM_MOUSEMOVE:

			break;
		case WM_LBUTTONUP:

			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
};
