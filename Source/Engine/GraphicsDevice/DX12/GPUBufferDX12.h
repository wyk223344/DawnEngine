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

		GPUBufferDX12(GPUDeviceDX12* device)
			: GPUResourceDX12<GPUBuffer>(device)
		{
		}

		void ReleaseView()
		{
			m_SRV.Release();
			m_UAV.Release();
		}

		void SetSRV(D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc)
		{
			m_SRV.CreateSRV(m_Device, GetResource(), srvDesc);
		}

		void SetUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc, ID3D12Resource* counterResource = nullptr)
		{
			m_UAV.CreateUAV(m_Device, GetResource(), uavDesc, counterResource);
		}

		void GetVBView(D3D12_VERTEX_BUFFER_VIEW& view) const
		{
			view.StrideInBytes = GetStride();
			view.SizeInBytes = (UINT)GetSizeInBytes();
			view.BufferLocation = GetLocation();
		}

		void GetIBView(D3D12_INDEX_BUFFER_VIEW& view) const
		{
			view.Format = GetStride() == 4 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
			view.SizeInBytes = (UINT)GetSizeInBytes();
			view.BufferLocation = GetLocation();
		}

	public:

		D3D12_CPU_DESCRIPTOR_HANDLE SRV() const { return m_SRV.CPU(); }

		D3D12_CPU_DESCRIPTOR_HANDLE UAV() const { return m_UAV.CPU(); }

	protected:

		bool OnInit() override;

		void OnReleaseGPU() override;

	private:

		DescriptorHeapWithSlotsDX12::Slot m_SRV, m_UAV;
	};
}

#endif