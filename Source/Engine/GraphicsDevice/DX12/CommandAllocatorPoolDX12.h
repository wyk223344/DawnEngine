#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Include.h"
#include "IncludeDX12Headers.h"

#include <vector>
#include <queue>

namespace DawnEngine::DX12
{
	class GPUDeviceDX12;

	class CommandAllocatorPoolDX12
	{
	private:

		typedef Pair<uint64, ID3D12CommandAllocator*> PoolPair;

		const D3D12_COMMAND_LIST_TYPE m_Type;
		GPUDeviceDX12* m_Device;
		std::vector<ID3D12CommandAllocator*> m_Pool;
		std::queue<PoolPair> m_Ready;

	public:

		CommandAllocatorPoolDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type);
		~CommandAllocatorPoolDX12();

	public:

		uint32 Size() const
		{
			return m_Pool.size();
		}

	public:

		ID3D12CommandAllocator* RequestAllocator(uint64 completedFenceValue);

		void DiscardAllocator(uint64 fenceValue, ID3D12CommandAllocator* allocator);

		void Release();
	};
}

#endif