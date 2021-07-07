#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/CreateWindowSettings.h"
#include "Engine/Platform/Types.h"
#include <string.h>

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
        // static Window* CreateWindow(const CreateWindowSettings& settings) = delete;

        // 根据大小和对齐方式分配内存
        static void* Allocate(uint64 size, uint64 alignment) = delete;

        // 释放一块分配的内存
        static void Free(void* ptr) = delete;

        /// <summary>
        /// Performs an atomic 32-bit variable read operation on the specified values.
        /// </summary>
        /// <param name="dst">A pointer to the destination value.</param>
        /// <returns>The function returns the value of the destination parameter.</returns>
        static int32 AtomicRead(int32 volatile* dst) = delete;

        /// <summary>
        /// Performs an atomic 64-bit variable read operation on the specified values.
        /// </summary>
        /// <param name="dst">A pointer to the destination value.</param>
        /// <returns>The function returns the value of the destination parameter.</returns>
        static int64 AtomicRead(int64 volatile* dst) = delete;

        /// <summary>
        /// Sets a 32-bit variable to the specified value as an atomic operation.
        /// </summary>
        /// <param name="dst">A pointer to the value to be exchanged.</param>
        /// <param name="value">The value to be set.</param>
        static void AtomicStore(int32 volatile* dst, int32 value) = delete;

        /// <summary>
        /// Sets a 64-bit variable to the specified value as an atomic operation.
        /// </summary>
        /// <param name="dst">A pointer to the value to be exchanged.</param>
        /// <param name="value">The value to be set.</param>
        static void AtomicStore(int64 volatile* dst, int64 value) = delete;

    public:

        // 拷贝内存
        static void MemoryCopy(void* dst, const void* src, uint64 size)
        {
            memcpy(dst, src, static_cast<size_t>(size));
        }

        // 设置内存值
        static void MemorySet(void* dst, uint64 size, int32 value)
        {
            memset(dst, value, static_cast<size_t>(size));
        }

        // 清理内存
        static void MemoryClear(void* dst, uint64 size)
        {
            memset(dst, 0, static_cast<size_t>(size));
        }

        // 比较内存
        static int32 MemoryCompare(const void* buf1, const void* buf2, uint64 size)
        {
            return memcmp(buf1, buf2, static_cast<size_t>(size));
        }
    };

}