#pragma once

#if PLATFORM_WINDOWS

#include "Engine/Platform/Windows/IncludeWindowsHeader.h"
#include "Engine/Platform/Base/WindowBase.h"


class WindowsWindow : public WindowBase
{
private:
    HWND__* m_Handle;

    unsigned int m_Width;
    unsigned int m_Height;

public:
    WindowsWindow(const CreateWindowSettings& settings);
    ~WindowsWindow();

public:

    void* GetNativePtr() const override;

    unsigned int GetWidth() const;

    unsigned int GetHeight() const;
};


#endif