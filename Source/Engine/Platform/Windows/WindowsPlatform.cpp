#if PLATFORM_WINDOWS

#include "IncludeWindowsHeader.h"
#include "Engine/Platform/Platform.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Core/Memory/Memory.h"

#include <string>

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void WindowsPlatform::PreInit(void* hInstance)
{

	// ×¢²á´°¿ÚÀà
	HINSTANCE mhAppInst = (HINSTANCE)hInstance;
	WNDCLASS windowsClass;
	windowsClass.style = CS_HREDRAW | CS_VREDRAW;
	windowsClass.lpfnWndProc = MainWndProc;
	windowsClass.cbClsExtra = 0;
	windowsClass.cbWndExtra = 0;
	windowsClass.hInstance = mhAppInst;
	windowsClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	windowsClass.hCursor = LoadCursor(0, IDC_ARROW);
	windowsClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	windowsClass.lpszMenuName = 0;
	windowsClass.lpszClassName = L"MainWnd";
	if (!RegisterClass(&windowsClass))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return;
	}
	RECT R = { 0, 0, 800, 600 };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;
	std::wstring mMainWndCaption = L"d3d App";
	HWND handle = CreateWindowW(L"MainWnd", L"DawnEngine",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0);
	if (!handle)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return;
	}

	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}


void WindowsPlatform::Tick()
{
	MSG msg;
	// If there are Window messages then process them.
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	Globals::IsRequestingExit = msg.message == WM_QUIT;
}

void* WindowsPlatform::Allocate(uint64 size, uint64 alignment)
{
	void* ptr = _aligned_malloc((size_t)size, (size_t)alignment);
	return ptr;
}

void WindowsPlatform::Free(void* ptr)
{
	_aligned_free(ptr);
}

Window* WindowsPlatform::CreateWindow(const CreateWindowSettings& settings)
{
	return New<WindowsWindow>(settings);
}







#endif