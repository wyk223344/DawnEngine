#pragma once

#include "Engine/Graphics/GPUConstantBuffer.h"
#include "GPUResourceDX12.h"
#include "IncludeDX12Headers.h"

namespace DawnEngine::DX12
{
	class GPUConstantBufferDX12 : public GPUResourceDX12<GPUConstantBuffer>
	{
	public:

		GPUConstantBufferDX12(GPUDeviceDX12* device, uint32 size)
			: GPUResourceDX12<GPUConstantBuffer>(device)
			, GPUAddress(0)
		{
			m_Size = size;
		}

	public:

		D3D12_GPU_VIRTUAL_ADDRESS GPUAddress;

	};
}