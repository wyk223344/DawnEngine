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
	bool isCubeMap = m_Desc.IsCubeMap();
	bool isVolume = m_Desc.IsVolume();
	int32 mipLevels = m_Desc.MipLevels;
	int32 depthOrArraySize = m_Desc.IsVolume() ? m_Desc.Depth : m_Desc.ArraySize;

	DXGI_FORMAT format = RenderToolsDX12::ToDxgiFormat(Format());

	ID3D12Resource* resource;

	D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;

	D3D12_RESOURCE_DESC resourceDesc;
	resourceDesc.MipLevels = mipLevels;
	resourceDesc.Format = format;
	resourceDesc.Width = Width();
	resourceDesc.Height = Height();
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	resourceDesc.DepthOrArraySize = depthOrArraySize;
	resourceDesc.SampleDesc.Count = static_cast<UINT>(MultiSampleLevel());
	resourceDesc.SampleDesc.Quality = 0;
	resourceDesc.Alignment = 0;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resourceDesc.Dimension = isVolume ? D3D12_RESOURCE_DIMENSION_TEXTURE3D : D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	
	if (useRTV)
	{
		resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		initialState = D3D12_RESOURCE_STATE_RENDER_TARGET;
	}
	else if (useDSV)
	{
		resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		initialState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
		if (!useSRV)
		{
			resourceDesc.Flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
		}
		LOG_WARNING("Init Depth Texture");
	}
	else if (useSRV)
	{
		initialState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
	}

	D3D12_HEAP_PROPERTIES heapProperties;
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperties.CreationNodeMask = 1;
	heapProperties.VisibleNodeMask = 1;

	
	if (useDSV)
	{
		D3D12_CLEAR_VALUE clearValue;
		clearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		clearValue.DepthStencil.Depth = 1.0f;
		clearValue.DepthStencil.Stencil = 0;

		auto result = m_Device->GetDevice()->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			initialState,
			&clearValue,
			IID_PPV_ARGS(&resource)
		);
		ThrowIfFailed(result);
	}
	else
	{
		auto result = m_Device->GetDevice()->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			initialState,
			nullptr,
			IID_PPV_ARGS(&resource)
		);
		ThrowIfFailed(result);
	}

	InitResource(resource, initialState);

	// ³õÊ¼»¯ÃèÊö·û

	if (useRTV)
	{
		D3D12_RENDER_TARGET_VIEW_DESC rtDesc;
		rtDesc.Format = format;
		rtDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		rtDesc.Texture2D.MipSlice = 0;
		rtDesc.Texture2D.PlaneSlice = 0;
		SetRTV(&rtDesc);
	}

	if (useSRV)
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		if (useDSV)
		{
			srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		}

		if (isCubeMap)
		{
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
			srvDesc.TextureCube.MostDetailedMip = 0;
			srvDesc.TextureCube.MipLevels = mipLevels;
			srvDesc.TextureCube.ResourceMinLODClamp = 0;
		}
		else
		{
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = m_Desc.MipLevels;
			srvDesc.Texture2D.PlaneSlice = 0;
			srvDesc.Texture2D.ResourceMinLODClamp = 0;
		}

		SetSRV(&srvDesc);
	}
	
	if (useDSV)
	{
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		dsvDesc.Format = format;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		
		SetDSV(&dsvDesc);
	}
	
	return true;
}

#endif