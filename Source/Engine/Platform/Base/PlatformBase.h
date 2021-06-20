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
        static Window* CreateWindow(const CreateWindowSettings& settings) = delete;

        // ���ݴ�С�Ͷ��뷽ʽ�����ڴ�
        static void* Allocate(uint64 size, uint64 alignment) = delete;

        // �ͷ�һ�������ڴ�
        static void Free(void* ptr) = delete;
    };

}