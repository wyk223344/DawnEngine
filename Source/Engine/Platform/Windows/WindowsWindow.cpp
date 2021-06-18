#if PLATFORM_WINDOWS

#include "Engine/Platform/Platform.h"
#include "Engine/Platform/Windows/IncludeWindowsHeader.h"
#include "Engine/Platform/Windows/WindowsWindow.h"

#include <string>


using namespace DawnEngine;


WindowsWindow::WindowsWindow(const CreateWindowSettings& settings) : WindowBase(settings)
{
    m_Width = settings.Width;
    m_Height = settings.Height;
	m_Handle = nullptr;

	RECT R = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	std::wstring mMainWndCaption = L"d3d App";
	HWND handle = CreateWindowW(
		L"MainWnd",
		L"DawnEngine",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_Width,
		m_Height,
		0,
		0,
		(HINSTANCE)Platform::InstanceHandle,
		0);

	if (!handle)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return;
	}
	m_Handle = handle;
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}


WindowsWindow::~WindowsWindow()
{
}


void* WindowsWindow::GetNativePtr() const
{
    return m_Handle;
}

unsigned int WindowsWindow::GetWidth() const
{
    return m_Width;
}

unsigned int WindowsWindow::GetHeight() const
{
    return m_Height;
}


#endif