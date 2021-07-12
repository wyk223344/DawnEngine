#pragma once

#include "Engine/Core/Types/BaseTypes.h"

namespace DawnEngine
{

    class Globals
    {
    public:

        // 如果为true，则表示游戏要退出了
        static bool IsRequestingExit;

        // 退出码，表示退出原因
        static int32 ExitCode;

        // 屏幕宽度
        static int32 Width;

        // 屏幕高度
        static int32 Height;

    public:  // 测试用数据

        // 摄像机到中心点距离
        static float Distance2Center;
    };

}