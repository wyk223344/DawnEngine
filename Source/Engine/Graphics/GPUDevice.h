#pragma once


#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUSwapChain.h"
#include "Engine/Graphics/GPUBuffer.h"
#include "Engine/Platform/Platform.h"

namespace DawnEngine
{
    /*
        GPU Device
    */
    class GPUDevice
    {
    public:

        static GPUDevice* Instance;

    public: // 对外接口虚函数
        
        // 获取渲染Context
        virtual GPUContext* GetMainContext() = 0;

        // 创建交换链
        virtual GPUSwapChain* CreateSwapChain(Window* window) = 0;

        // 创建Buffer
        virtual GPUBuffer* CreateBuffer() = 0;

    public: // 声明周期相关虚函数

        // 初始化
        virtual bool Init();

        // 进行绘制
        virtual void Draw();

        // 销毁
        virtual void Dispose();

    protected:
    };

}