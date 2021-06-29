#pragma once


#if GRAPHICS_API_DIRECTX12

#include "GPUDeviceDX12.h"
#include "GPUResourceDX12.h"
#include "IncludeDX12Headers.h"
#include "GPUTextureDX12.h"
#include "Engine/Graphics/GPUSwapChain.h"
#include "Engine/Platform/Window.h"

namespace DawnEngine::DX12
{
	class GPUSwapChainDX12 : public GPUResourceDX12<GPUSwapChain>
	{
	public:

		GPUSwapChainDX12(GPUDeviceDX12* device, Window* window)
			: GPUResourceDX12<GPUSwapChain>(device)
			, m_WindowHandle(static_cast<HWND>(window->GetNativePtr()))
			, m_SwapChain(nullptr)
			, m_CurrentFrameIndex(0)
		{
			m_Window = window;
			for (int i = 0; i < DX12_BACK_BUFFER_COUNT; i++)
			{
				m_SwapChainBuffers[i].InitDevice(device);
			}
		}

	public:

		void Resize(uint32 width, uint32 height) override;
		void Present(bool vsync = false) override;
		GPUTexture* GetBackBuffer() override;

	public:

		HWND m_WindowHandle;
		IDXGISwapChain3* m_SwapChain;
		int32 m_CurrentFrameIndex;

		GPUTextureDX12 m_SwapChainBuffers[DX12_BACK_BUFFER_COUNT];

		// temp
		// Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffers[DX12_BACK_BUFFER_COUNT];
		//DescriptorHeapWithSlotsDX12::Slot m_SwapChainSlots[DX12_BACK_BUFFER_COUNT];
	};

}

#endif