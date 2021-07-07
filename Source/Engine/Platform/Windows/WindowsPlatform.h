#pragma once

#if PLATFORM_WINDOWS

#include "Engine/Platform/Base/PlatformBase.h"
#include "Engine/Platform/Windows/IncludeWindowsHeader.h"

namespace DawnEngine
{

    class WindowsPlatform : public PlatformBase
    {
    public:

        // windowsƽ̨��ʵ�����
        static void* InstanceHandle;

    public:

        // Ԥ��ʼ��Platform����Initǰ����
        static void PreInit(void* hInstance);

    public: // override

        static void Tick();
        static void* Allocate(uint64 size, uint64 alignment);
        static void Free(void* ptr);

        static Window* CreateWindow(const CreateWindowSettings& settings);

        static int32 AtomicRead(int32 volatile* dst);
        static int64 AtomicRead(int64 volatile* dst);
        static void AtomicStore(int32 volatile* dst, int32 value);
        static void AtomicStore(int64 volatile* dst, int64 value);
    };
}

#endif