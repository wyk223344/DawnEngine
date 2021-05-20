#pragma once

#if PLATFORM_WINDOWS

#include "Engine/Platform/Base/PlatformBase.h"


class WindowsPlatform : public PlatformBase
{

public: // new public function

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