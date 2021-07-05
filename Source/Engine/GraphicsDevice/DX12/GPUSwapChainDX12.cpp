#if GRAPHICS_API_DIRECTX12

#include "CommandQueueDX12.h"
#include "GPUSwapChainDX12.h"
#include "Engine/Core/Include.h"
#include "GPUTextureDX12.h"
#include "Engine/Graphics/Textures/GPUTexture.h"

using namespace DawnEngine;
using namespace DawnEngine::DX12;


void GPUSwapChainDX12::Resize(uint32 width, uint32 height)
{
	if (width == m_Width && height == m_Height)
	{
		return;
	}
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	if (m_SwapChain == nullptr)
	{
		swapChainDesc.Width = width;
		swapChainDesc.Height = height;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = FALSE;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = DX12_BACK_BUFFER_COUNT;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc;
		fullscreenDesc.RefreshRate.Numerator = 0;
		fullscreenDesc.RefreshRate.Denominator = 1;
		fullscreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		fullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		fullscreenDesc.Windowed = TRUE;

		IDXGISwapChain1* swapChain;
		auto dxgiFactory = m_Device->GetDXGIFactory();
		ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
			m_Device->GetGraphicsQueue()->GetCommandQueue(),
			m_WindowHandle,
			&swapChainDesc,
			&fullscreenDesc,
			nullptr,
			&swapChain)
		);
		m_SwapChain = static_cast<IDXGISwapChain3*>(swapChain);
		m_SwapChain->SetBackgroundColor((const DXGI_RGBA*)Color::Black.Raw);
	}
	else
	{
		for (int32 i = 0; i < DX12_BACK_BUFFER_COUNT; i++)
		{
			m_SwapChainBuffers[i].Release();
		}

		m_SwapChain->GetDesc1(&swapChainDesc);
		ThrowIfFailed(m_SwapChain->ResizeBuffers(swapChainDesc.BufferCount, width, height, swapChainDesc.Format, swapChainDesc.Flags));
	}
	m_Width = width;
	m_Height = height;
	m_CurrentFrameIndex = m_SwapChain->GetCurrentBackBufferIndex();

	// Ë¢ÐÂ»º´æ
	for (int32 i = 0; i < DX12_BACK_BUFFER_COUNT; i++)
	{
		ID3D12Resource* backbuffer;
		m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&backbuffer));
		m_SwapChainBuffers[i].CreateFromSwapChain(backbuffer, this);
		//ThrowIfFailed(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&(backBuffer.GetResource()))));
		// m_SwapChainSlots[i].CreateRTV(m_Device, m_SwapChainBuffers[i].Get(), nullptr);
	}
}

void GPUSwapChainDX12::Present(bool vsync)
{
	ThrowIfFailed(m_SwapChain->Present(0, 0));
	m_CurrentFrameIndex = m_SwapChain->GetCurrentBackBufferIndex();
}


GPUTexture* GPUSwapChainDX12::GetBackBuffer()
{
	return &m_SwapChainBuffers[m_CurrentFrameIndex];
}


#endif