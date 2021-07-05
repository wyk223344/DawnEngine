#if GRAPHICS_API_DIRECTX12

#include "GPUSwapChainDX12.h"
#include "GPUTextureDX12.h"

using namespace DawnEngine::DX12;

void GPUTextureDX12::CreateFromSwapChain(ID3D12Resource* resource, GPUSwapChainDX12* swapChain)
{
	InitResource(resource, D3D12_RESOURCE_STATE_PRESENT);
	SetRTV(nullptr);
	m_Desc = GPUTextureDescription::New2D(swapChain->GetWidth(), swapChain->GetHeight(), PixelFormat::R8G8B8A8_UNorm);
}

bool GPUTextureDX12::OnInit()
{
	return true;
}

#endif