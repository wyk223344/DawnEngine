#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/GraphicsDevice/DX12/IncludeDX12Headers.h"

namespace DawnEngine::DX12
{
	class GPUResource
	{
	public:
		GPUResource() :
			m_GpuVirtualAddress(D3D12_GPU_VIRTUAL_ADDRESS_NULL),
			m_UsageState(D3D12_RESOURCE_STATE_COMMON),
			m_TransitioningState((D3D12_RESOURCE_STATES)-1)
		{
		}

		GPUResource(ID3D12Resource* resource, D3D12_RESOURCE_STATES state) :
			m_GpuVirtualAddress(D3D12_GPU_VIRTUAL_ADDRESS_NULL),
			m_Resource(resource),
			m_UsageState(state),
			m_TransitioningState((D3D12_RESOURCE_STATES)-1)
		{
		}

		~GPUResource() { Destroy(); }

		virtual void Destroy()
		{
			m_Resource = nullptr;
			m_GpuVirtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_NULL;
		}

		ID3D12Resource* operator->() { return m_Resource.Get(); }
		const ID3D12Resource* operator->() const { return m_Resource.Get(); }

		ID3D12Resource* GetResource() { return m_Resource.Get(); }
		const ID3D12Resource* GetResource() const { return m_Resource.Get(); }

		ID3D12Resource** GetAddressOf() { return m_Resource.GetAddressOf(); }

	protected:
		Microsoft::WRL::ComPtr<ID3D12Resource> m_Resource;
		D3D12_RESOURCE_STATES m_UsageState;
		D3D12_RESOURCE_STATES m_TransitioningState;
		D3D12_GPU_VIRTUAL_ADDRESS m_GpuVirtualAddress;

	};
}

#endif