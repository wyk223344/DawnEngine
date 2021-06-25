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

	public:

		GPUResourceStateDX12 State;

	private:

		ID3D12Resource* m_Resource;

	};

	class IShaderResourceDX12
	{
	public:
	
		IShaderResourceDX12()
			: SubresourceIndex(D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES)
		{
		}

		IShaderResourceDX12(int32 subresourceIndex)
			: SubresourceIndex(subresourceIndex)
		{
		}

		// Gets CPU handle to the render target view descriptor.
		virtual D3D12_CPU_DESCRIPTOR_HANDLE RTV() const = 0;

		// Gets CPU handle to the shader resource view descriptor.
		virtual D3D12_CPU_DESCRIPTOR_HANDLE SRV() const = 0;

		// Gets CPU handle to the depth stencil view descriptor.
		virtual D3D12_CPU_DESCRIPTOR_HANDLE DSV() const = 0;

		// Gets CPU handle to the unordered access view descriptor.
		virtual D3D12_CPU_DESCRIPTOR_HANDLE UAV() const = 0;

		// Determines whether this resource is depth/stencil buffer.
		virtual bool IsDepthStencilResource() const = 0;

		// Gets the resource owner.
		virtual GPUResourceOwnerDX12* GetResourceOwner() const = 0;

	public:

		// Affected subresource index or -1 if use whole resource.
		int32 SubresourceIndex;
	};

}

#endif