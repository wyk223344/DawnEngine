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

	class GPUContextDX12 : GPUContext
	{
	public:

		GPUContextDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type);

		~GPUContextDX12();

	public:

		// ����CommandList�������µ�Allocator
		void Reset();

	public:  // override

		void FrameBegin() override;
		void FrameEnd() override;

	private:

		// �����Դ����
		void addResourceBarrier(ID3D12Resource* resource, const D3D12_RESOURCE_STATES before, const D3D12_RESOURCE_STATES after);

		// ������Դ����
		void flushResourceBarriers();

	private:

		GPUDeviceDX12* m_Device;
		ID3D12GraphicsCommandList* m_CommandList;
		ID3D12CommandAllocator* m_CurrentAllocator;
		// GPUPipelineStateDX12* m_CurrentState;

		D3D12_RESOURCE_BARRIER m_ResourceBarrierBuffers[DX12_RB_BUFFER_SIZE];
		int32 m_ResourceBarrierNum;
	};

}

#endif