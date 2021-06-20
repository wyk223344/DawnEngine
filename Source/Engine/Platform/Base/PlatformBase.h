#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/CreateWindowSettings.h"
#include "Engine/Platform/Types.h"

namespace DawnEngine
{

    class PlatformBase
    {

    public:

        // 初始化Platform, true表示成功初始化，false表示初始化失败
        static bool Init();

        // 记录log到文件
        static void LogInfo();

        // 在正式进入游戏主循环前调用
        static void BeforeRun();

        // 在主线程游戏主循环中调用
        static void Tick();

        // 在引擎退出前(还未进行清理)调用
        static void BeforeExit();

        // 在引擎退出后(已完成清理)调用
        static void Exit();

    public:

        // 创建窗口
        static Window* CreateWindow(const CreateWindowSettings& settings) = delete;

        // 根据大小和对齐方式分配内存
        static void* Allocate(uint64 size, uint64 alignment) = delete;

        // 释放一块分配的内存
        static void Free(void* ptr) = delete;
    };

}