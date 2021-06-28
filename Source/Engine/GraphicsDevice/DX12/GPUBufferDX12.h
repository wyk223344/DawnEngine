#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Include.h"
#include "Engine/Graphics/GPUBuffer.h"
#include "GPUResourceDX12.h"
#include "GPUDeviceDX12.h"
#include "DescriptorHeapDX12.h"


namespace DawnEngine::DX12
{

	class GPUBufferDX12 : public GPUResourceDX12<GPUBuffer>, public GPUResourceOwnerDX12
	{
	public:

		void Release()
		{
			m_SRV.Release();
			m_UAV.Release();
		}

		void SetSRV(D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc)
		{
			if (srvDesc)
			{
				m_SRV.CreateSRV(m_Device, GetResource(), srvDesc);
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
				m_UAV.CreateUAV(m_Device, GetResource(), uavDesc, counterResource);
			}
			else
			{
				m_UAV.Release();
			}
		}

	public:

		D3D12_CPU_DESCRIPTOR_HANDLE SRV() const { return m_SRV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE UAV() const { return m_UAV.CPU(); }

	private:

		DescriptorHeapWithSlotsDX12::Slot m_SRV, m_UAV;
	};
}

#endif