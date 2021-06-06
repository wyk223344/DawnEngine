#pragma once

#if PLATFORM_WINDOWS

#include "Engine/Platform/Windows/IncludeWindowsHeader.h"
#include "Engine/Platform/Base/WindowBase.h"


class WindowsWindow : public WindowBase
{
private:
    HWND__* _handle;

public:
    /// <summary>
    /// Initializes a new instance of the <see cref="WindowsWindow"/> class.
    /// </summary>
    /// <param name="settings">The initial window settings.</param>
    WindowsWindow(const CreateWindowSettings& settings);

    /// <summary>
    /// Finalizes an instance of the <see cref="WindowsWindow"/> class.
    /// </summary>
    ~WindowsWindow();

public:

    void* GetNativePtr() const override;
};


#endif