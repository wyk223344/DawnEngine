#pragma once

#if GRAPHICS_API_DIRECTX12


#include "Engine/Graphics/GPUDevice.h"
#include "Engine/GraphicsDevice/DX12/IncludeDX12Headers.h"
#include "Engine/GraphicsDevice/DX12/GPUContextDX12.h"


namespace DawnEngine::DX12
{
	class Engine;
	class WindowsWindow;
	class GPUContextDX12;
	class GPUSwapChainDX12;
	class UploadBufferDX12;
	class CommandQueueDX12;
	class CommandSignatureDX12;

	class GPUDeviceDX12 : public GPUDevice
	{
	public:
		static const DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		static const DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
		static const int SwapChainBufferCount = 2;

	public:
		static GPUDevice* Create();

	public:
		// GPUContext* GetMainContext() override;

		ID3D12Device* GetDevice() const
		{
			return m_Device;
		}

	public: // override
		bool Init() override;
		void Draw() override;
		void Dispose() override;

	private:

	public:
		UploadBufferDX12* UploadBuffer;

	private:
		ID3D12Device* m_Device;
		IDXGIFactory4* m_FactoryDXGI;
		ID3D12RootSignature* m_RootSignature;

		CommandQueueDX12* m_CommandQueue;
		GPUContextDX12* m_MainContext;

	};

}

#endif