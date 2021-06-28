#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/GPUResourceState.h"
#include "IncludeDX12Headers.h"

// 无效的资源状态
#define D3D12_RESOURCE_STATE_CORRUPT (D3D12_RESOURCE_STATES)-1

namespace DawnEngine::DX12
{
	class GPUResourceStateDX12 : public GPUResourceState<D3D12_RESOURCE_STATES, D3D12_RESOURCE_STATE_CORRUPT>
	{
	public:
		static bool IsTransitionNeeded(D3D12_RESOURCE_STATES currentState, D3D12_RESOURCE_STATES targetState)
		{
			return currentState != targetState && ((currentState | targetState) != currentState || targetState == D3D12_RESOURCE_STATE_COMMON);
		}
	};
}


#endif