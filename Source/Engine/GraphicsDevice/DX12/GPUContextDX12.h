#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/GPUContext.h"

/*
	DX12执行命令流程:
	1. 假设已经有了ID3D12Device

	2. 生成一个围栏ID3D12Fence
		ID3D12Device->CreateFence

	3. 创建针对该设备的命令队列: ID3D12CommandQueue
		ID3D12Device->CreateCommandQueue

	4. 创建一个命令分配器:ID3D12CommandAllocator（对应你所要执行的命令类型）
		ID3D12Device->CreateCommandAllocator

	5. 使用该命令分配器生成一个命令列表: ID3D12CommandList
		ID3D12Device->CreateCommandList

	6. 向命令列表中插入命令
		ID3D12CommandList->xxx		// 插入命令
		ID3D12CommandList->xxx		// 插入命令
		ID3D12CommandList->close(); // 关闭

	7. 发送给GPU执行命令
		ID3D12CommandQueue->ExecuteCommandLists

	8. 插入围栏值
		ID3D12CommandQueue-Signal

	9. 其他操作，交换缓冲区等，不属于这里的功能
*/


namespace DawnEngine::DX12
{
	class GPUDeviceDX12;
	class GPUPipelineStateDX12;
	class GPUBufferDX12;
	class GPUConstantBufferDX12;
	class GPUTextureViewDX12;

	class GPUContextDX12 : GPUContext
	{
	private:
		GPUDeviceDX12* m_Device;
		ID3D12GraphicsCommandList* m_CommandList;
		ID3D12CommandAllocator* m_CurrentAllocator;
		GPUPipelineStateDX12* m_CurrentState;
	};

}

#endif