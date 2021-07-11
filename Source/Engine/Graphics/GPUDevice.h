#pragma once


#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUSwapChain.h"
#include "Engine/Graphics/GPUBuffer.h"
#include "Engine/Platform/Platform.h"

namespace DawnEngine
{
    class GPUShader;
    class GPUPipelineState;
    class GPUConstantBuffer;

    /*
        GPU Device
    */
    class GPUDevice
    {
    public:

        static GPUDevice* Instance;

    public:

        // 是否正在绘制中
        bool IsRendering() const { return m_IsRendering; }

    public: // 对外接口虚函数
        
        // 获取渲染Context
        virtual GPUContext* GetMainContext() = 0;

        // 创建交换链
        virtual GPUSwapChain* CreateSwapChain(Window* window) = 0;

        // 创建Buffer
        virtual GPUBuffer* CreateBuffer() = 0;

        // 创建shader
        virtual GPUShader* CreateShader() = 0;

        // 创建pipeline state
        virtual GPUPipelineState* CreatePipelineState() = 0;

        // 创建常量缓冲区
        virtual GPUConstantBuffer* CreateConstantBuffer(uint32 size) = 0;

    public: // 声明周期相关虚函数

        // 初始化
        virtual bool Init();

        // 绘制执行前
        virtual void DrawBegin();

        // 进行绘制
        virtual void Draw();

        // 绘制执行后
        virtual void DrawEnd();

        // 销毁
        virtual void Dispose();

    protected:

        bool m_IsRendering;
    };

}