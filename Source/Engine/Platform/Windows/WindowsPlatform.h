#pragma once

#if PLATFORM_WINDOWS

#include "Engine/Platform/Base/PlatformBase.h"
#include "Engine/Platform/Windows/IncludeWindowsHeader.h"

class WindowsPlatform : public PlatformBase
{
public:
    // windows平台的实例句柄
    static void* InstanceHandle;

public:

    /// <summary>
    /// Pre initialize platform.
    /// </summary>
    /// <param name="hInstance">The Win32 application instance.</param>
    static void PreInit(void* hInstance);

public: // override

    static void Tick();
    static void* Allocate(uint64 size, uint64 alignment);
    static void Free(void* ptr);

    static Window* CreateWindow(const CreateWindowSettings& settings);
};


#endif