#if PLATFORM_WINDOWS

#include "Engine/Platform/Windows/WindowsWindow.h"


WindowsWindow::WindowsWindow(const CreateWindowSettings& settings) : WindowBase(settings)
{
}


WindowsWindow::~WindowsWindow()
{
}


void* WindowsWindow::GetNativePtr() const
{
    return _handle;
}


#endif