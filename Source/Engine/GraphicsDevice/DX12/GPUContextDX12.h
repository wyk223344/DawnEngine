#pragma once

#if GRAPHICS_API_DIRECTX12

#include "IncludeDX12Headers.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Core/Include.h"

/*
	DX12ִ����������:
	1. �����Ѿ�����ID3D12Device

	2. ����һ��Χ��ID3D12Fence
		ID3D12Device->CreateFence

	3. ������Ը��豸���������: ID3D12CommandQueue
		ID3D12Device->CreateCommandQueue

	4. ����һ�����������:ID3D12CommandAllocator����Ӧ����Ҫִ�е��������ͣ�
		ID3D12Device->CreateCommandAllocator

	5. ʹ�ø��������������һ�������б�: ID3D12CommandList
		ID3D12Device->CreateCommandList

	6. �������б��в�������
		ID3D12CommandList->xxx		// ��������
		ID3D12CommandList->xxx		// ��������
		ID3D12CommandList->close(); // �ر�

	7. ���͸�GPUִ������
		ID3D12CommandQueue->ExecuteCommandLists

	8. ����Χ��ֵ
		ID3D12CommandQueue-Signal

	9. ���������������������ȣ�����������Ĺ���
*/



namespace DawnEngine::DX12
{
	class GPUDeviceDX12;
	class GPUTextureDX12;
	class GPUPipelineStateDX12;
	class GPUResourceOwnerDX12;

	class GPUContextDX12 : GPUContext
	{
	public:

		GPUContextDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type);

		~GPUContextDX12();

	public:

		// ����CommandList�������µ�Allocator
		void Reset();

		// ������Դ״̬
		void SetResourceState(GPUResourceOwnerDX12* resource, D3D12_RESOURCE_STATES after, int32 subresourceIndex = -1);

		// ִ��ָ��
		uint64 Execute(bool waitForCompletion = false);

		// ��ȡCommandList
		ID3D12GraphicsCommandList* GetCommandList() const
		{
			return m_CommandList;
		}

	public:  // override

		void FrameBegin() override;
		void FrameEnd() override;
		void SetViewport(const Math::Viewport& viewport) override;
		void SetScissor(const Math::Rectangle& scissorRect) override;
		void Clear(GPUTexture* rt, const Color& color) override;
		void SetRenderTarget(GPUTexture* rt) override;
		void SetRenderTarget(GPUTexture* rt, GPUTexture* depthBuffer) override;
		void BindVB(GPUBuffer* vertexBuffer) override;
		void BindIB(GPUBuffer* indexBuffer) override;
		void UpdateBuffer(GPUBuffer* buffer, const void* data, uint32 size, uint32 offset) override;
		void DrawIndexedInstanced(uint32 indicesCount, uint32 instanceCount, int32 startIndex = 0, int32 startVertex = 0, int32 startInstance = 0) override;
		void SetState(GPUPipelineState* state) override;
		GPUPipelineState* GetState() const override;
		void ClearState() override;
		void FlushState() override;
		void Flush() override;

	private:

		// �����Դ����
		void addResourceBarrier(ID3D12Resource* resource, const D3D12_RESOURCE_STATES before, const D3D12_RESOURCE_STATES after);

		// ������ɫ����Դ��ͼ
		void flushSRVs();

		// ������ȾĿ����ͼ
		void flushRTVs();
		
		// �������������ͼ
		void flushUAVs();

		// ���ó���������, ConstantBuffer
		void flushCBs();

		// ������Դ����, ResourceBarrier
		void flushRBs();

		// ����PipelineState
		void flushPS();

	private:

		GPUDeviceDX12* m_Device;
		ID3D12GraphicsCommandList* m_CommandList;
		ID3D12CommandAllocator* m_CurrentAllocator;
		GPUPipelineStateDX12* m_CurrentState;

		D3D12_RESOURCE_BARRIER m_ResourceBarrierBuffers[DX12_RB_BUFFER_SIZE];
		int32 m_ResourceBarrierNum;

		D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;
		D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;

		GPUTextureDX12* m_RenderTargetTexture;
		GPUTextureDX12* m_DepthTexture;
		bool m_RTDirtyFlag = false;
	};

}

#endif