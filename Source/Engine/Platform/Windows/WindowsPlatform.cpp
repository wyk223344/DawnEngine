#if PLATFORM_WINDOWS

#include "IncludeWindowsHeader.h"
#include "Engine/Platform/Platform.h"
#include "Engine/Platform/Window.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Core/Memory/Memory.h"
#include "WindowsInput.h"
#include "Engine/Platform/WindowsManager.h"
#include "ThirdParty/imgui/imgui_impl_win32.h"
#include <string>

using namespace DawnEngine;


void* WindowsPlatform::InstanceHandle = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
	if (hwnd != nullptr)
	{
		// Find window by handle
		const auto win = WindowsManager::GetByNativePtr(hwnd);
		if (win)
		{
			return static_cast<WindowsWindow*>(win)->WndProc(msg, wParam, lParam);
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void WindowsPlatform::PreInit(void* hInstance)
{
	WindowsPlatform::InstanceHandle = hInstance;
	// ע�ᴰ����
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
}

bool WindowsPlatform::Init()
{
	WindowsInput::Init();
	return true;
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

int64 WindowsPlatform::DoInterlockedExchange(int64 volatile* dst, int64 exchange)
{
	return InterlockedExchange64(dst, exchange);
}

int32 WindowsPlatform::DoInterlockedCompareExchange(int32 volatile* dst, int32 exchange, int32 comperand)
{
	static_assert(sizeof(int32) == sizeof(LONG), "Invalid LONG size.");
	return _InterlockedCompareExchange((LONG volatile*)dst, exchange, comperand);
}

int64 WindowsPlatform::DoInterlockedCompareExchange(int64 volatile* dst, int64 exchange, int64 comperand)
{
	return InterlockedCompareExchange64(dst, exchange, comperand);
}

int64 WindowsPlatform::DoInterlockedIncrement(int64 volatile* dst)
{
	return InterlockedIncrement64(dst);
}

int64 WindowsPlatform::DoInterlockedDecrement(int64 volatile* dst)
{
	return InterlockedDecrement64(dst);
}

int64 WindowsPlatform::DoInterlockedAdd(int64 volatile* dst, int64 value)
{
	return InterlockedExchangeAdd64(dst, value);
}

int32 WindowsPlatform::AtomicRead(int32 volatile* dst)
{
	static_assert(sizeof(int32) == sizeof(LONG), "Invalid LONG size.");
	return _InterlockedCompareExchange((LONG volatile*)dst, 0, 0);
}

int64 WindowsPlatform::AtomicRead(int64 volatile* dst)
{
	return InterlockedCompareExchange64(dst, 0, 0);
}

void WindowsPlatform::AtomicStore(int32 volatile* dst, int32 value)
{
	static_assert(sizeof(int32) == sizeof(LONG), "Invalid LONG size.");
	_InterlockedExchange((LONG volatile*)dst, value);
}

void WindowsPlatform::AtomicStore(int64 volatile* dst, int64 value)
{
	InterlockedExchange64(dst, value);
}


#endif