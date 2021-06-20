#pragma once


#if GRAPHICS_API_DIRECTX12

#include "GPUDeviceDX12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Graphics/GPUSwapChain.h"
#include "Engine/Platform/Window.h"

namespace DawnEngine::DX12
{
	class GPUSwapChainDX12 : GPUResourceDX12<GPUSwapChain>
	{
	public:

		GPUSwapChainDX12(GPUDeviceDX12* device, Window* window)
			: GPUResourceDX12(device)
			, m_WindowHandle(static_cast<HWND>(window->GetNativePtr()))
			, m_SwapChain(nullptr)
			, m_CurrentFrameIndex(0)
		{
			m_Window = window;
		}

	public:

		void Resize(uint32 width, uint32 height) override;

	private:

		HWND m_WindowHandle;
		IDXGISwapChain3* m_SwapChain;
		int32 m_CurrentFrameIndex;

		// temp
		Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffer[DX12_BACK_BUFFER_COUNT];
	};

}

#endif