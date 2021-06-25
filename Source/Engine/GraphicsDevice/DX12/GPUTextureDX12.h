#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/Textures/GPUTexture.h"

#include "GPUDeviceDX12.h"
#include "GPUResourceDX12.h"
#include "DescriptorHeapDX12.h"


namespace DawnEngine::DX12
{
	class GPUTextureViewDX12 : public GPUTextureView, public IShaderResourceDX12
	{
	public:

		GPUTextureViewDX12()
		{
		}

	public:

		void Init(GPUResource* parent, GPUDeviceDX12* device, GPUResourceOwnerDX12* owner, PixelFormat format, MSAALevel msaa, int32 subresourceIndex = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES)
		{
			GPUTextureView::Init(parent, format, msaa);
			SubresourceIndex = subresourceIndex;
			m_Device = device;
			m_Owner = owner;
		}

		// Release the view
		void Release()
		{
			m_RTV.Release();
			m_SRV.Release();
			m_DSV.Release();
			m_UAV.Release();
		}

		void SetRTV(D3D12_RENDER_TARGET_VIEW_DESC* rtvDesc)
		{
			if (rtvDesc)
			{
				m_RTV.CreateRTV(m_Device, m_Owner->GetResource(), rtvDesc);
			}
			else
			{
				m_RTV.Release();
			}
		}

		void SetSRV(D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc)
		{
			if (srvDesc)
			{
				m_SRV.CreateSRV(m_Device, m_Owner->GetResource(), srvDesc);
			}
			else
			{
				m_SRV.Release();
			}
		}

		void SetDSV(D3D12_DEPTH_STENCIL_VIEW_DESC* dsvDesc)
		{
			if (dsvDesc)
			{
				m_DSV.CreateDSV(m_Device, m_Owner->GetResource(), dsvDesc);
			}
			else
			{
				m_DSV.Release();
			}
		}

		void SetUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc, ID3D12Resource* counterResource = nullptr)
		{
			if (uavDesc)
			{
				m_UAV.CreateUAV(m_Device, m_Owner->GetResource(), uavDesc, counterResource);
			}
			else
			{
				m_UAV.Release();
			}
		}

	public:  // override IShaderResourceDX12

		D3D12_CPU_DESCRIPTOR_HANDLE RTV() const override { return m_RTV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE SRV() const override { return m_SRV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE DSV() const override { return m_DSV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE UAV() const override { return m_UAV.CPU(); }

		bool IsDepthStencilResource() const override { return m_DSV.IsValid(); }

		GPUResourceOwnerDX12* GetResourceOwner() const override { return m_Owner; }

	private:

		GPUDeviceDX12* m_Device = nullptr;
		GPUResourceOwnerDX12* m_Owner = nullptr;
		DescriptorHeapWithSlotsDX12::Slot m_RTV, m_SRV, m_DSV, m_UAV;
	};


	class GPUTextureDX12 : public GPUResourceDX12<GPUTexture>, public GPUResourceOwnerDX12
	{
	public:

		GPUTextureView* View() const override { return (GPUTextureView*)m_View; }

	private:

		GPUTextureViewDX12* m_View;
	};

}


#endif