#if GRAPHICS_API_DIRECTX12

#include "GPUSwapChainDX12.h"
#include "GPUTextureDX12.h"

using namespace DawnEngine::DX12;


#pragma region GPUTextureViewDX12

void GPUTextureViewDX12::Init(GPUTextureDX12* parent, GPUDeviceDX12* device, int32 subresourceIndex)
{
	GPUTextureView::Init(parent);
	m_Owner = parent;
	m_Device = device;
	SubresourceIndex = subresourceIndex;
}

#pragma endregion


#pragma region GPUTextureDX12

void GPUTextureDX12::CreateFromSwapChain(ID3D12Resource* resource, GPUSwapChainDX12* swapChain)
{
	InitResource(resource, D3D12_RESOURCE_STATE_PRESENT);
	D3D12_RENDER_TARGET_VIEW_DESC rtDesc;
	rtDesc.Format = RenderToolsDX12::ToDxgiFormat(PixelFormat::R8G8B8A8_UNorm);
	rtDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtDesc.Texture2D.MipSlice = 0;
	rtDesc.Texture2D.PlaneSlice = 0;
	m_HandlesPerSlice.resize(1);
	m_HandlesPerSlice[0].Init(this, m_Device);
	m_HandlesPerSlice[0].SetRTV(nullptr);
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
	int32 arraySize = m_Desc.ArraySize;
	bool isArray = arraySize > 1;

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

	InitResource(resource, initialState, resourceDesc.DepthOrArraySize * resourceDesc.MipLevels);

	// 初始化描述符
	D3D12_RENDER_TARGET_VIEW_DESC rtDesc;
	rtDesc.Format = format;

	D3D12_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = format;
	srDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	D3D12_DEPTH_STENCIL_VIEW_DESC dsDesc;
	dsDesc.Format = format;
	dsDesc.Flags = D3D12_DSV_FLAG_NONE;

	if (isArray)
	{
		// 初始化每个slice的Handle
		m_HandlesPerSlice.resize(arraySize);
		for (int32 arrayIndex = 0; arrayIndex < arraySize; arrayIndex++)
		{
			m_HandlesPerSlice[arrayIndex].Init(this, m_Device, arrayIndex);
			
			if (useDSV)
			{
				dsDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
				dsDesc.Texture2DArray.ArraySize = 1;
				dsDesc.Texture2DArray.FirstArraySlice = arrayIndex;
				dsDesc.Texture2DArray.MipSlice = 0;
				m_HandlesPerSlice[arrayIndex].SetDSV(&dsDesc);
			}
			if (useRTV)
			{
				rtDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
				rtDesc.Texture2DArray.ArraySize = 1;
				rtDesc.Texture2DArray.FirstArraySlice = arrayIndex;
				rtDesc.Texture2DArray.MipSlice = 0;
				rtDesc.Texture2DArray.PlaneSlice = 0;
				m_HandlesPerSlice[arrayIndex].SetRTV(&rtDesc);
			}
			if (useSRV)
			{
				srDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
				srDesc.Texture2DArray.ArraySize = 1;
				srDesc.Texture2DArray.FirstArraySlice = arrayIndex;
				srDesc.Texture2DArray.MipLevels = mipLevels;
				srDesc.Texture2DArray.MostDetailedMip = 0;
				srDesc.Texture2DArray.PlaneSlice = 0;
				srDesc.Texture2DArray.ResourceMinLODClamp = 0;
				m_HandlesPerSlice[arrayIndex].SetSRV(&srDesc);
			}
		}
		// 初始化总体的handle
		{
			m_HandleArray.Init(this, m_Device);
			if (useDSV)
			{
				dsDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
				dsDesc.Texture2DArray.ArraySize = arraySize;
				dsDesc.Texture2DArray.FirstArraySlice = 0;
				dsDesc.Texture2DArray.MipSlice = 0;
				m_HandleArray.SetDSV(&dsDesc);
			}
			if (useRTV)
			{
				rtDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
				rtDesc.Texture2DArray.ArraySize = arraySize;
				rtDesc.Texture2DArray.FirstArraySlice = 0;
				rtDesc.Texture2DArray.MipSlice = 0;
				rtDesc.Texture2DArray.PlaneSlice = 0;
				m_HandleArray.SetRTV(&rtDesc);
			}
			if (useSRV)
			{
				if (isCubeMap)
				{
					srDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
					srDesc.TextureCube.MostDetailedMip = 0;
					srDesc.TextureCube.MipLevels = mipLevels;
					srDesc.TextureCube.ResourceMinLODClamp = 0;
				}
				else
				{
					srDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
					srDesc.Texture2DArray.ArraySize = arraySize;
					srDesc.Texture2DArray.FirstArraySlice = 0;
					srDesc.Texture2DArray.MipLevels = mipLevels;
					srDesc.Texture2DArray.MostDetailedMip = 0;
					srDesc.Texture2DArray.ResourceMinLODClamp = 0;
					srDesc.Texture2DArray.PlaneSlice = 0;
				}
				m_HandleArray.SetSRV(&srDesc);
			}
		}
	}
	else
	{
		m_HandlesPerSlice.resize(1);
		m_HandlesPerSlice[0].Init(this, m_Device);
		if (useDSV)
		{
			dsDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
			dsDesc.Texture2D.MipSlice = 0;
			m_HandlesPerSlice[0].SetDSV(&dsDesc);
		}
		if (useRTV)
		{
			rtDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
			rtDesc.Texture2D.MipSlice = 0;
			rtDesc.Texture2D.PlaneSlice = 0;
			m_HandlesPerSlice[0].SetRTV(&rtDesc);
		}
		if (useSRV)
		{
			if (useDSV)
			{
				srDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			}
			srDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			srDesc.Texture2D.MostDetailedMip = 0;
			srDesc.Texture2D.MipLevels = mipLevels;
			srDesc.Texture2D.ResourceMinLODClamp = 0;
			srDesc.Texture2D.PlaneSlice = 0;
			m_HandlesPerSlice[0].SetSRV(&srDesc);
		}
	}

	/*if (useRTV)
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
	}*/


	
	return true;
}


#pragma endregion

#endif