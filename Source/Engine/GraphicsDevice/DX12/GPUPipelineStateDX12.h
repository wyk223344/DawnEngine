#pragma once

#if GRAPHICS_API_DIRECTX12

#include "GPUResourceDX12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/PixelFormat.h"

#include <map>

namespace DawnEngine::DX12
{
	class GPUTextureDX12;
	class GPUTextureViewDX12;

	struct GPUPipelineStateKeyDX12
	{
		MSAALevel MSAA;
		PixelFormat DepthFormat;
		PixelFormat RenderTargetFormat;

		bool operator==(const GPUPipelineStateKeyDX12& other) const
		{
			return Platform::MemoryCompare((void*)this, &other, sizeof(GPUPipelineStateKeyDX12)) == 0;
		}

		friend inline uint32 GetHash(const GPUPipelineStateKeyDX12& key)
		{
			uint32 hash = (int32)key.MSAA * 11;
			CombineHash(hash, (uint32)key.DepthFormat * 93473262);
			CombineHash(hash, (uint32)key.RenderTargetFormat);
			return hash;
		}
	};


	class GPUPipelineStateDX12 : public GPUResourceDX12<GPUPipelineState>
	{
	public:

		GPUPipelineStateDX12(GPUDeviceDX12* device)
			: GPUResourceDX12<GPUPipelineState>(device)
		{
			m_PSOCache.clear();
		}

		ID3D12PipelineState* GetState(GPUTextureViewDX12* depthHandle, GPUTextureViewDX12* rtHandle);

	protected:

		bool OnInit() override;

	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_PipelineStateDescDX12;
		std::map<uint32, ID3D12PipelineState*> m_PSOCache;
	};

}

#endif