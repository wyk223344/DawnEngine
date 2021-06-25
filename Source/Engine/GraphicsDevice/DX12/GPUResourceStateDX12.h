#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/GPUResourceState.h"
#include "IncludeDX12Headers.h"

// ��Ч����Դ״̬
#define D3D12_RESOURCE_STATE_CORRUPT (D3D12_RESOURCE_STATES)-1

namespace DawnEngine::DX12
{
	class GPUResourceStateDX12 : public GPUResourceState<D3D12_RESOURCE_STATES, D3D12_RESOURCE_STATE_CORRUPT>
	{

	};
}


#endif