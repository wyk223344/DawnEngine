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
    };

}