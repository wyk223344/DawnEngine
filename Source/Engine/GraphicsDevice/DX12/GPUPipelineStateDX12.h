#pragma once

#if GRAPHICS_API_DIRECTX12

#include "GPUResourceDX12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Graphics/GPUPipelineState.h"


namespace DawnEngine::DX12
{

	class GPUPipelineStateDX12 : public GPUResourceDX12<GPUPipelineState>
	{
	public:
	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_PipelineStateDescDX12;
	};

}

#endif