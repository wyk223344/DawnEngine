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
			, m_SubresourceCount(0)
		{
		}

		~GPUResourceOwnerDX12()
		{
		}

	public:

		ID3D12Resource* GetResource() const { return m_Resource; }

		uint32 GetSubresourcesCount() const { return m_SubresourceCount; }

		D3D12_GPU_VIRTUAL_ADDRESS GetLocation() const { return m_Resource->GetGPUVirtualAddress(); }

		void InitResource(ID3D12Resource* resource, const D3D12_RESOURCE_STATES initialState, const uint32 subresourceCount = 1)
		{
			m_Resource = resource;
			m_SubresourceCount = subresourceCount;
			State.Initialize(subresourceCount, initialState);
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
		uint32 m_SubresourceCount;

	};

	class IShaderResourceDX12
	{
	public:

		IShaderResourceDX12()
			: SubresourceIndex(0)
		{
		}

	public:

		int32 SubresourceIndex;

	public:

		virtual bool IsDepthStencilResource() const = 0;

		virtual D3D12_CPU_DESCRIPTOR_HANDLE SRV() const = 0;

		virtual D3D12_CPU_DESCRIPTOR_HANDLE UAV() const = 0;

		virtual GPUResourceOwnerDX12* GetResourceOwner() const = 0;

	};
}

#endif