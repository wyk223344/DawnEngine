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
	bool useSRV = m_Desc.IsShaderResource();
	bool useRTV = m_Desc.IsRenderTarget();
	bool useDSV = m_Desc.IsDepthStencil();
	DXGI_FORMAT format = RenderToolsDX12::ToDxgiFormat(Format());

	ID3D12Resource* resource;

	D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;

	D3D12_RESOURCE_DESC resourceDesc;
	resourceDesc.MipLevels = m_Desc.MipLevels;
	resourceDesc.Format = format;
	resourceDesc.Width = Width();
	resourceDesc.Height = Height();
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	resourceDesc.DepthOrArraySize = m_Desc.IsVolume() ? m_Desc.Depth : m_Desc.ArraySize;
	resourceDesc.SampleDesc.Count = static_cast<UINT>(MultiSampleLevel());
	resourceDesc.SampleDesc.Quality = 0;
	resourceDesc.Alignment = 0;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resourceDesc.Dimension = m_Desc.IsVolume() ? D3D12_RESOURCE_DIMENSION_TEXTURE3D : D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	
	if (useRTV)
	{
		resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		initialState = D3D12_RESOURCE_STATE_RENDER_TARGET;
	}
	else if (useDSV)
	{
		resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		initialState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	}
	if (useSRV)
	{
		initialState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
	}

	D3D12_HEAP_PROPERTIES heapProperties;
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperties.CreationNodeMask = 1;
	heapProperties.VisibleNodeMask = 1;

	auto result = m_Device->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		initialState,
		nullptr,
		IID_PPV_ARGS(&resource)
		);
	ThrowIfFailed(result);

	InitResource(resource, initialState);

	// ³õÊ¼»¯ÃèÊö·û

	if (useRTV)
	{

	}

	if (useSRV)
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = m_Desc.MipLevels;
		srvDesc.Texture2D.PlaneSlice = 0;
		srvDesc.Texture2D.ResourceMinLODClamp = 0;

		SetSRV(&srvDesc);
	}
	

	
	return true;
}

#endif