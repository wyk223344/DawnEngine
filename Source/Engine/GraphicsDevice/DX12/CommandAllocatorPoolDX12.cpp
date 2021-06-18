#if GRAPHICS_API_DIRECTX12

#include "CommandAllocatorPoolDX12.h"
#include "GPUDeviceDX12.h"

using namespace DawnEngine::DX12;

CommandAllocatorPoolDX12::CommandAllocatorPoolDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type)
	: m_Type(type)
	, m_Device(device)
{
}

CommandAllocatorPoolDX12::~CommandAllocatorPoolDX12()
{
	Release();
}

ID3D12CommandAllocator* CommandAllocatorPoolDX12::RequestAllocator(uint64 completedFenceValue)
{
	ID3D12CommandAllocator* allocator = nullptr;
	if (!m_Ready.empty())
	{
		PoolPair& firstPair = m_Ready.front();
		if (firstPair.First <= completedFenceValue)
		{
			allocator = firstPair.Second;
			ThrowIfFailed(allocator->Reset());
			m_Ready.pop();
		}
	}
	if (allocator == nullptr)
	{
		ThrowIfFailed(m_Device->GetDevice()->CreateCommandAllocator(m_Type, IID_PPV_ARGS(&allocator)));
		m_Pool.push_back(allocator);
	}
	return allocator;
}

void CommandAllocatorPoolDX12::DiscardAllocator(uint64 fenceValue, ID3D12CommandAllocator* allocator)
{
	m_Ready.push(PoolPair(fenceValue, allocator));
}

void CommandAllocatorPoolDX12::Release()
{
	for (int32 i = 0; i < m_Pool.size(); i++)
	{
		m_Pool[i]->Release();
	}
	m_Pool.clear();
}



#endif