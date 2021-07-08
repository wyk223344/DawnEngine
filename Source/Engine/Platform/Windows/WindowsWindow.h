#pragma once

#if PLATFORM_WINDOWS

#include "Engine/Platform/Windows/IncludeWindowsHeader.h"
#include "Engine/Platform/Base/WindowBase.h"

namespace DawnEngine
{

    class WindowsWindow : public WindowBase
    {
    public:

        WindowsWindow(const CreateWindowSettings& settings);
        ~WindowsWindow();

    public:

        LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

    public: // override

        void* GetNativePtr() const override { return m_Handle; }

    private:

        HWND__* m_Handle;
    };
}

#endif