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

        // �Ƿ����ڻ�����
        bool IsRendering() const { return m_IsRendering; }

    public: // ����ӿ��麯��
        
        // ��ȡ��ȾContext
        virtual GPUContext* GetMainContext() = 0;

        // ����������
        virtual GPUSwapChain* CreateSwapChain(Window* window) = 0;

        // ����Buffer
        virtual GPUBuffer* CreateBuffer() = 0;

        // ����shader
        virtual GPUShader* CreateShader() = 0;

        // ����pipeline state
        virtual GPUPipelineState* CreatePipelineState() = 0;

        // ��������������
        virtual GPUConstantBuffer* CreateConstantBuffer(uint32 size) = 0;

    public: // ������������麯��

        // ��ʼ��
        virtual bool Init();

        // ����ִ��ǰ
        virtual void DrawBegin();

        // ���л���
        virtual void Draw();

        // ����ִ�к�
        virtual void DrawEnd();

        // ����
        virtual void Dispose();

    protected:

        bool m_IsRendering;
    };

}