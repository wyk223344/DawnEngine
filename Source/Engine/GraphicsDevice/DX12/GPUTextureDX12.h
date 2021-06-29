#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/Textures/GPUTexture.h"

#include "GPUDeviceDX12.h"
#include "GPUResourceDX12.h"
#include "DescriptorHeapDX12.h"


namespace DawnEngine::DX12
{

	class GPUTextureDX12 : public GPUResourceDX12<GPUTexture>, public GPUResourceOwnerDX12
	{
	public:

		GPUTextureDX12()
			: GPUResourceDX12<GPUTexture>(nullptr)
		{
		}

		GPUTextureDX12(GPUDeviceDX12* device)
			: GPUResourceDX12<GPUTexture>(device)
		{
		}

		void Release()
		{
			ReleaseResource();
			m_RTV.Release();
			m_SRV.Release();
			m_DSV.Release();
			m_UAV.Release();
		}

		void SetRTV(D3D12_RENDER_TARGET_VIEW_DESC* rtvDesc)
		{
			m_RTV.CreateRTV(m_Device, GetResource(), rtvDesc);
		}

		void SetSRV(D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc)
		{
			m_SRV.CreateSRV(m_Device, GetResource(), srvDesc);
		}

		void SetDSV(D3D12_DEPTH_STENCIL_VIEW_DESC* dsvDesc)
		{
			m_DSV.CreateDSV(m_Device, GetResource(), dsvDesc);
		}

		void SetUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc, ID3D12Resource* counterResource = nullptr)
		{
			m_UAV.CreateUAV(m_Device, GetResource(), uavDesc, counterResource);
		}

	public:

		D3D12_CPU_DESCRIPTOR_HANDLE RTV() const { return m_RTV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE SRV() const { return m_SRV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE DSV() const { return m_DSV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE UAV() const { return m_UAV.CPU(); }

		bool IsDepthStencilResource() const { return m_DSV.IsValid(); }

	private:

		DescriptorHeapWithSlotsDX12::Slot m_RTV, m_SRV, m_DSV, m_UAV;
	};

}


#endif