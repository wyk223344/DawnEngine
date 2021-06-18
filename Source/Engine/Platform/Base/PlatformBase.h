#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/CreateWindowSettings.h"
#include "Engine/Platform/Types.h"

namespace DawnEngine
{

    class PlatformBase
    {

    public:
        /// <summary>
        /// ��ʼ��Platform
        /// </summary>
        /// <returns>true��ʾ�ɹ���ʼ����false��ʾ��ʼ��ʧ��.</returns>
        static bool Init();

        /// <summary>
        /// ��¼log���ļ�
        /// </summary>
        static void LogInfo();

        /// <summary>
        /// ����ʽ������Ϸ��ѭ��ǰ����
        /// </summary>
        static void BeforeRun();

        /// <summary>
        /// �����߳���Ϸ��ѭ���е���
        /// </summary>
        static void Tick();

        /// <summary>
        /// �������˳�ǰ(��δ��������)����
        /// </summary>
        static void BeforeExit();

        /// <summary>
        /// �������˳���(���������)����
        /// </summary>
        static void Exit();

    public:

        /// <summary>
        /// Suspends the execution of the current thread until the time-out interval elapses
        /// </summary>
        /// <param name="milliseconds">The time interval for which execution is to be suspended, in milliseconds.</param>
        static void Sleep(int32 milliseconds) = delete;

        /// <summary>
        /// Creates the window.
        /// </summary>
        /// <param name="settings">The window settings</param>
        /// <returns></returns>
        static Window* CreateWindow(const CreateWindowSettings& settings) = delete;

        /// <summary>
        /// Allocates memory on a specified alignment boundary.
        /// </summary>
        /// <param name="size">The size of the allocation (in bytes).</param>
        /// <param name="alignment">The memory alignment (in bytes). Must be an integer power of 2.</param>
        /// <returns>The pointer to the allocated chunk of the memory. The pointer is a multiple of alignment.</returns>
        static void* Allocate(uint64 size, uint64 alignment) = delete;

        /// <summary>
        /// Frees a block of allocated memory.
        /// </summary>
        /// <param name="ptr">A pointer to the memory block to deallocate.</param>
        static void Free(void* ptr) = delete;
    };

}