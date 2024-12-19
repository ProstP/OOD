#pragma once
#include "../../Lw10/Resource.h"
#include "../Controller/Controller.h"
#include "../Model/ShapeStore.h"
#include "../Types/Types.h"
#include "ClassicCanvas.h"
#include <iostream>
#include <vector>
#include <windows.h>

using namespace Types;

const int HALF_SIDE = 3;

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
	Rect m_menuRect = { 0, 0, CANVAS_WIDTH, 50 };
	Rect m_canvasRect = { 0, 60, CANVAS_WIDTH, CANVAS_HEIGHT };
	HINSTANCE m_hInstance;
	Model::ShapeStore& m_store;
	Controller m_controller;
	bool m_isDragging = false;
	bool m_isResizing = false;

	void RegistWindow()
	{
		WNDCLASSEXW wcex = { 0 };

		wcex.cbSize = sizeof(WNDCLASSEXW);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = &View::WndProc;
		wcex.hInstance = m_hInstance;
		wcex.lpszClassName = L"MyWindowClass";
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

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
		View* view;
		if (message == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			view = reinterpret_cast<View*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(view));
		}
		else
		{
			view = reinterpret_cast<View*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}

		switch (message)
		{
		case WM_GETMINMAXINFO: {
			MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(lParam);

			mmi->ptMinTrackSize.x = CANVAS_WIDTH + 16;
			mmi->ptMinTrackSize.y = 60 + CANVAS_HEIGHT + 38;
			mmi->ptMaxTrackSize.x = CANVAS_WIDTH + 16;
			mmi->ptMaxTrackSize.y = 60 + CANVAS_HEIGHT + 38;
		}

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
			Rectangle(hdc, 0, 0, view->m_menuRect.width, view->m_canvasRect.top + view->m_canvasRect.height);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			DeleteObject(pbrush);

			view->ViewMenu(hdc);
			view->ViewCanvas(hdc);

			EndPaint(hWnd, &ps);
		}
		break;
		case WM_LBUTTONDOWN: {
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (y <= static_cast<int>(view->m_menuRect.height))
			{
				view->ClickToMenu(x, y);
			}
			else
			{
				view->ClickToCanvas(x, y, hWnd);
			}
			InvalidateRect(hWnd, nullptr, TRUE);
		}
		break;
		case WM_MOUSEMOVE: {
			if (view->m_isDragging)
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);

				view->m_controller.DragShapeTo({ x, y - 60 });

				InvalidateRect(hWnd, nullptr, TRUE);
			}

			if (view->m_isResizing)
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);

				view->m_controller.Resize({ x, y });

				InvalidateRect(hWnd, nullptr, TRUE);
			}
		}
		break;
		case WM_MOUSELEAVE:
		case WM_LBUTTONUP: {
			if (view->m_isDragging)
			{
				view->m_isDragging = false;
				//ReleaseCapture();
			}
			if (view->m_isResizing)
			{
				view->m_isResizing = false;
				view->m_controller.EndResize();
			}
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

	void ViewMenu(HDC hdc)
	{
		HBRUSH background = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, background);

		Rectangle(hdc, m_menuRect.left, m_menuRect.top,
			m_menuRect.left + m_menuRect.width, m_menuRect.top + m_menuRect.height);

		HBRUSH color = CreateSolidBrush(RGB(0, 0, 230));
		SelectObject(hdc, color);

		DeleteObject(background);

		Rectangle(hdc, 20, 10, 50, 40);
		Ellipse(hdc, 70, 10, 100, 40);

		POINT triangle[3] = {
			{ 135, 10 },
			{ 120, 40 },
			{ 150, 40 }
		};
		Polygon(hdc, triangle, 3);

		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		DeleteObject(color);

		if (m_controller.GetIndexOfSelected() != -1)
		{
			HBRUSH colorForDelete = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, colorForDelete);

			int offsetFromVertices = 5;
			int offsetFromCenter = 5;

			POINT deleteIcon[12]{
				{ 170 + offsetFromVertices, 10 },
				{ 185, 25 - offsetFromCenter },
				{ 200 - offsetFromVertices, 10 },
				{ 200, 10 + offsetFromVertices },
				{ 185 + offsetFromCenter, 25 },
				{ 200, 40 - offsetFromVertices },
				{ 200 - offsetFromCenter, 40 },
				{ 185, 25 + offsetFromCenter },
				{ 170 + offsetFromVertices, 40 },
				{ 170, 40 - offsetFromVertices },
				{ 185 - offsetFromCenter, 25 },
				{ 170, 10 + offsetFromVertices }
			};

			Polygon(hdc, deleteIcon, 12);

			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			DeleteObject(colorForDelete);
		}
	}

	void ViewCanvas(HDC hdc)
	{
		HBRUSH background = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, background);

		Rectangle(hdc, m_canvasRect.left, m_canvasRect.top,
			m_canvasRect.left + m_canvasRect.width, m_canvasRect.top + m_canvasRect.height);

		HBRUSH color = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hdc, color);

		DeleteObject(background);

		ClassicCanvas canvas(hdc, 60);
		for (int i = 0; i < m_store.GetShapesCount(); i++)
		{
			m_store.GetAt(i)->Draw(canvas);
		}

		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		DeleteObject(color);

		int selected = m_controller.GetIndexOfSelected();

		if (m_store.GetAt(selected) != nullptr)
		{
			HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 200));
			SelectObject(hdc, hpen);

			Rect rect = m_store.GetAt(selected)->GetRect();

			Rectangle(hdc, rect.left, rect.top + 60, rect.left + rect.width, rect.top + rect.height + 60);

			HBRUSH vertColor = CreateSolidBrush(RGB(0, 0, 230));
			SelectObject(hdc, vertColor);

			DeleteObject(hpen);

			Rectangle(hdc, rect.left - HALF_SIDE, rect.top - HALF_SIDE + 60, rect.left + HALF_SIDE, rect.top + HALF_SIDE + 60);

			Rectangle(hdc, rect.left - HALF_SIDE, rect.top + rect.height - HALF_SIDE + 60,
				rect.left + HALF_SIDE, rect.top + rect.height + HALF_SIDE + 60);

			Rectangle(hdc, rect.left + rect.width - HALF_SIDE, rect.top - HALF_SIDE + 60,
				rect.left + rect.width + HALF_SIDE, rect.top + HALF_SIDE + 60);

			Rectangle(hdc, rect.left + rect.width - HALF_SIDE, rect.top + rect.height - HALF_SIDE + 60,
				rect.left + rect.width + HALF_SIDE, rect.top + rect.height + HALF_SIDE + 60);
		}
	}

	void ClickToMenu(int x, int y)
	{
		if (20 <= x && x <= 50 && 10 <= y && y <= 40)
		{
			m_controller.CreateRectangle();
		}
		else if (70 <= x && x <= 100 && 10 <= y && y <= 40)
		{
			m_controller.CreateEllipse();
		}
		else if (120 <= x && x <= 150 && 10 <= y && y <= 40)
		{
			m_controller.CreateTriangle();
		}
		else if (m_controller.GetIndexOfSelected() != -1
			&& 170 <= x && x <= 200 && 10 <= y && y <= 40)
		{
			m_controller.DeleteShape();
		}
	}

	void ClickToCanvas(int x, int y, HWND hWnd)
	{
		if (m_controller.GetIndexOfSelected() != -1)
		{
			Rect rect = m_store.GetAt(m_controller.GetIndexOfSelected())->GetRect();
			rect.top += 60;

			if (CheckClickToVert(rect.left, rect.top, x, y))
			{
				m_controller.StartResize(Vertices::UL, { x, y });
				m_isResizing = true;
				RegistMouseToLeave(hWnd);
				return;
			}
			else if (CheckClickToVert(rect.left + rect.width, rect.top, x, y))
			{
				m_controller.StartResize(Vertices::UR, { x, y });
				m_isResizing = true;
				RegistMouseToLeave(hWnd);
				return;
			}
			else if (CheckClickToVert(rect.left + rect.width, rect.top + rect.height, x, y))
			{
				m_controller.StartResize(Vertices::DR, { x, y });
				m_isResizing = true;
				RegistMouseToLeave(hWnd);
				return;
			}
			else if (CheckClickToVert(rect.left, rect.top + rect.height, x, y))
			{
				m_controller.StartResize(Vertices::DL, { x, y });
				m_isResizing = true;
				RegistMouseToLeave(hWnd);
				return;
			}
		}

		m_controller.Select({ x, y - 60 });

		if (m_controller.GetIndexOfSelected() != -1)
		{
			m_isDragging = true;
			//SetCapture(hWnd);

			RegistMouseToLeave(hWnd);
		}
	}

	static bool CheckClickToVert(int vx, int vy, int mx, int my)
	{
		if (vx - HALF_SIDE <= mx && mx <= vx + HALF_SIDE && vy - HALF_SIDE <= my && my <= vy + HALF_SIDE)
		{
			return true;
		}

		return false;
	}

	static void RegistMouseToLeave(HWND hWnd)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.hwndTrack = hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = HOVER_DEFAULT;

		TrackMouseEvent(&tme);
	}
};
