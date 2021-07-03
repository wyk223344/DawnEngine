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

    public: // ����ӿ��麯��
        
        // ��ȡ��ȾContext
        virtual GPUContext* GetMainContext() = 0;

        // ����������
        virtual GPUSwapChain* CreateSwapChain(Window* window) = 0;

        // ����Buffer
        virtual GPUBuffer* CreateBuffer() = 0;

    public: // ������������麯��

        // ��ʼ��
        virtual bool Init();

        // ���л���
        virtual void Draw();

        // ����
        virtual void Dispose();

    protected:
    };

}