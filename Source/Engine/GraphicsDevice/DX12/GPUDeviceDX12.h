#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/GPUResource.h"
#include "Engine/Graphics/GPUDevice.h"
#include "IncludeDX12Headers.h"
#include "GPUContextDX12.h"
#include "DescriptorHeapDX12.h"


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

		GPUDeviceDX12();

		ID3D12Device* GetDevice() const { return m_Device; }

		IDXGIFactory4* GetDXGIFactory() const { return m_FactoryDXGI; }

		ID3D12RootSignature* GetRootSignature() const { return m_RootSignature; }

		CommandQueueDX12* GetGraphicsQueue() const { return m_GraphicsQueue; }

	public: // override

		GPUContext* GetMainContext() override { return reinterpret_cast<GPUContext*>(m_MainContext); };

		GPUSwapChain* CreateSwapChain(Window* window) override;

		GPUBuffer* CreateBuffer() override;

		GPUShader* CreateShader() override;

		GPUPipelineState* CreatePipelineState() override;

	public: // override

		bool Init() override;
		void DrawBegin() override;
		void Dispose() override;

	private:

	public:

		DescriptorHeapPoolDX12 Heap_CBV_SRV_UAV;
		DescriptorHeapPoolDX12 Heap_RTV;
		DescriptorHeapPoolDX12 Heap_DSV;
		DescriptorHeapRingBufferDX12 RingHeap_CBV_SRV_UAV;

		UploadBufferDX12* UploadBuffer;

	private:

		ID3D12Device* m_Device;
		IDXGIFactory4* m_FactoryDXGI;
		ID3D12RootSignature* m_RootSignature;

		CommandQueueDX12* m_GraphicsQueue;
		GPUContextDX12* m_MainContext;
		
	};
}

#endif