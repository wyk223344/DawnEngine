#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Include.h"
#include "Engine/Graphics/GPUBuffer.h"
#include "GPUResourceDX12.h"
#include "GPUDeviceDX12.h"
#include "DescriptorHeapDX12.h"


namespace DawnEngine::DX12
{
	class GPUBufferViewDX12 : public GPUBufferView, public IShaderResourceDX12
	{
	public:

		GPUBufferViewDX12()
		{
		}

		~GPUBufferViewDX12()
		{
			Release();
		}

	public:

		void Init(GPUDeviceDX12* device, GPUResourceOwnerDX12* owner)
		{
			m_Device = device;
			m_Owner = owner;
		}

		void Release()
		{
			m_SRV.Release();
			m_UAV.Release();
		}

	public:

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

	public:  // override

		D3D12_CPU_DESCRIPTOR_HANDLE RTV() const override { return; }

		D3D12_CPU_DESCRIPTOR_HANDLE SRV() const override { return m_SRV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE DSV() const override { return; }

		D3D12_CPU_DESCRIPTOR_HANDLE UAV() const override { return m_UAV.CPU(); }

		bool IsDepthStencilResource() const override { return false; }

		GPUResourceOwnerDX12* GetResourceOwner() const override { return m_Owner; }

	private:

		GPUDeviceDX12* m_Device = nullptr;
		GPUResourceOwnerDX12* m_Owner = nullptr;
		DescriptorHeapWithSlotsDX12::Slot m_SRV, m_UAV;

	};

	class GPUBuffer : public GPUResourceDX12<GPUBuffer>, public GPUResourceOwnerDX12
	{
	private:

		GPUBufferViewDX12 m_View;
	};
}

#endif