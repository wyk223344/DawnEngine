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

	protected:

		ID3D12Resource* m_Resource;

	};

	class IShaderResourceDX12
	{
	public:

		IShaderResourceDX12()
		{
		}

	public:

		virtual bool IsDepthStencilResource() const = 0;

		virtual D3D12_CPU_DESCRIPTOR_HANDLE SRV() const = 0;

		virtual D3D12_CPU_DESCRIPTOR_HANDLE UAV() const = 0;

		virtual GPUResourceOwnerDX12* GetResourceOwner() const = 0;

	};
}

#endif