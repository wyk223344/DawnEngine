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

        // ��ʼ��Platform, true��ʾ�ɹ���ʼ����false��ʾ��ʼ��ʧ��
        static bool Init();

        // ��¼log���ļ�
        static void LogInfo();

        // ����ʽ������Ϸ��ѭ��ǰ����
        static void BeforeRun();

        // �����߳���Ϸ��ѭ���е���
        static void Tick();

        // �������˳�ǰ(��δ��������)����
        static void BeforeExit();

        // �������˳���(���������)����
        static void Exit();

    public:

        // ��������
        // static Window* CreateWindow(const CreateWindowSettings& settings) = delete;

        // ���ݴ�С�Ͷ��뷽ʽ�����ڴ�
        static void* Allocate(uint64 size, uint64 alignment) = delete;

        // �ͷ�һ�������ڴ�
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

        // �����ڴ�
        static void MemoryCopy(void* dst, const void* src, uint64 size)
        {
            memcpy(dst, src, static_cast<size_t>(size));
        }

        // �����ڴ�ֵ
        static void MemorySet(void* dst, uint64 size, int32 value)
        {
            memset(dst, value, static_cast<size_t>(size));
        }

        // �����ڴ�
        static void MemoryClear(void* dst, uint64 size)
        {
            memset(dst, 0, static_cast<size_t>(size));
        }

        // �Ƚ��ڴ�
        static int32 MemoryCompare(const void* buf1, const void* buf2, uint64 size)
        {
            return memcmp(buf1, buf2, static_cast<size_t>(size));
        }
    };

}