#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/Textures/GPUTexture.h"

#include "GPUDeviceDX12.h"
#include "GPUResourceDX12.h"
#include "DescriptorHeapDX12.h"

#include <vector>

namespace DawnEngine::DX12
{
	class GPUSwapChainDX12;

	class GPUTextureViewDX12 : public GPUTextureView, public IShaderResourceDX12
	{
	public:

		void Init(GPUTextureDX12* parent, GPUDeviceDX12* device, int32 subresourceIndex = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

		void Release()
		{
			m_RTV.Release();
			m_SRV.Release();
			m_DSV.Release();
			m_UAV.Release();
		}

	public:

		void SetRTV(D3D12_RENDER_TARGET_VIEW_DESC* rtvDesc)
		{
			m_RTV.CreateRTV(m_Device, m_Owner->GetResource(), rtvDesc);
		}

		void SetSRV(D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc)
		{
			m_SRV.CreateSRV(m_Device, m_Owner->GetResource(), srvDesc);
		}

		void SetDSV(D3D12_DEPTH_STENCIL_VIEW_DESC* dsvDesc)
		{
			m_DSV.CreateDSV(m_Device, m_Owner->GetResource(), dsvDesc);
		}

		void SetUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc, ID3D12Resource* counterResource = nullptr)
		{
			m_UAV.CreateUAV(m_Device, m_Owner->GetResource(), uavDesc, counterResource);
		}

	public:

		D3D12_CPU_DESCRIPTOR_HANDLE RTV() const { return m_RTV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE DSV() const { return m_DSV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE SRV() const override { return m_SRV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE UAV() const override { return m_UAV.CPU(); }

		GPUResourceOwnerDX12* GetResourceOwner() const override { return m_Owner; }

		bool IsDepthStencilResource() const override { return m_DSV.IsValid(); }

	private:

		GPUDeviceDX12* m_Device = nullptr;
		GPUResourceOwnerDX12* m_Owner = nullptr;
		DescriptorHeapWithSlotsDX12::Slot m_RTV, m_SRV, m_DSV, m_UAV;
	};

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
		}

	public:

		GPUTextureView* View(int32 arrayOrDepthIndex) const override
		{
			return (GPUTextureView*)&m_HandlesPerSlice[arrayOrDepthIndex];
		}

		GPUTextureView* ViewArray() const override
		{
			ASSERT(m_Desc.ArraySize > 1);
			return (GPUTextureView*)&m_HandleArray;
		}

	public:

		void CreateFromSwapChain(ID3D12Resource* resource, GPUSwapChainDX12* swapChain);

	protected:

		bool OnInit() override;

	private:

		std::vector<GPUTextureViewDX12> m_HandlesPerSlice;
		GPUTextureViewDX12 m_HandleArray;

	};

}


#endif