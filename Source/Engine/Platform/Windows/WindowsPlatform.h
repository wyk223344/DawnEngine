#pragma once

#if PLATFORM_WINDOWS

#include "Engine/Platform/Base/PlatformBase.h"
#include "Engine/Platform/Windows/IncludeWindowsHeader.h"

namespace DawnEngine
{

    class WindowsPlatform : public PlatformBase
    {
    public:

        // windows平台的实例句柄
        static void* InstanceHandle;

    public:

        // 预初始化Platform，在Init前调用
        static void PreInit(void* hInstance);

    public: // override

        static bool Init();
        static void Tick();
        static void* Allocate(uint64 size, uint64 alignment);
        static void Free(void* ptr);

        static Window* CreateWindow(const CreateWindowSettings& settings);

        static int64 DoInterlockedExchange(int64 volatile* dst, int64 exchange);
        static int32 DoInterlockedCompareExchange(int32 volatile* dst, int32 exchange, int32 comperand);
        static int64 DoInterlockedCompareExchange(int64 volatile* dst, int64 exchange, int64 comperand);
        static int64 DoInterlockedIncrement(int64 volatile* dst);
        static int64 DoInterlockedDecrement(int64 volatile* dst);
        static int64 DoInterlockedAdd(int64 volatile* dst, int64 value);
        static int32 AtomicRead(int32 volatile* dst);
        static int64 AtomicRead(int64 volatile* dst);
        static void AtomicStore(int32 volatile* dst, int32 value);
        static void AtomicStore(int64 volatile* dst, int64 value);
    };
}

#endif