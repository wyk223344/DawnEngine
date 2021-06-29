#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/GPUResource.h"
#include "IncludeDX12Headers.h"
#include "GPUResourceStateDX12.h"


namespace DawnEngine::DX12
{
	class GPUDeviceDX12;

	template<class BaseType>
	class GPUResourceDX12 : public GPUResourceBase<GPUDeviceDX12, BaseType>
	{
	public:
		GPUResourceDX12(GPUDeviceDX12* device)
			: GPUResourceBase(device)
		{
		}
	};

	class GPUResourceOwnerDX12 : public GPUResourceOwner
	{
	public:

		GPUResourceOwnerDX12()
			: m_Resource(nullptr)
		{
		}

		~GPUResourceOwnerDX12()
		{
		}

	public:

		ID3D12Resource* GetResource() const { return m_Resource; }

		D3D12_GPU_VIRTUAL_ADDRESS GetLocation() const { return m_Resource->GetGPUVirtualAddress(); }

		void InitResource(ID3D12Resource* resource, const D3D12_RESOURCE_STATES initialState)
		{
			m_Resource = resource;
			State.Initialize(initialState);
		}

		void ReleaseResource()
		{
			if (m_Resource)
			{
				m_Resource->Release();
				m_Resource = nullptr;
			}
		}

	public:

		GPUResourceStateDX12 State;

	private:

		ID3D12Resource* m_Resource;

	};

}

#endif