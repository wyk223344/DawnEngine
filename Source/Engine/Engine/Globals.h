#pragma once

#include "Engine/Core/Types/BaseTypes.h"

namespace DawnEngine
{

    class Globals
    {
    public:

        // ���Ϊtrue�����ʾ��ϷҪ�˳���
        static bool IsRequestingExit;

        // �˳��룬��ʾ�˳�ԭ��
        static int32 ExitCode;

        // ��Ļ���
        static int32 Width;

        // ��Ļ�߶�
        static int32 Height;

    public:  // ����������

        // ����������ĵ����
        static float Distance2Center;
    };

}