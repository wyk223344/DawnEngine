#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/CreateWindowSettings.h"
#include "Engine/Platform/Types.h"

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