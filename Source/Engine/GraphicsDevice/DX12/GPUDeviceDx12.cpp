
#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Include.h"
#include "GPUDeviceDX12.h"
#include "GPUContextDX12.h"
#include "CommandQueueDX12.h"
#include "d3dUtil.h"

using namespace DawnEngine;
using namespace DawnEngine::DX12;


GPUDevice* GPUDeviceDX12::Create()
{
	GPUDeviceDX12* device = New<GPUDeviceDX12>();
	if (!device->Init())
	{
		return nullptr;
	}
	return device;
}


bool GPUDeviceDX12::Init()
{
	
	// Create DXGI Factory
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&m_FactoryDXGI)));

	// Create Device
	ThrowIfFailed(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device)));

	// Spawn some info about the hardware
	D3D12_FEATURE_DATA_D3D12_OPTIONS options = {};
	ThrowIfFailed(m_Device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &options, sizeof(options)));
	LOG_INFO("Tiled Resources Tier: %s", options.TiledResourcesTier);
	LOG_INFO("Resource Binding Tier: %s", options.ResourceBindingTier);
	LOG_INFO("Conservative Rasterization Tier: %s", options.ConservativeRasterizationTier);
	LOG_INFO("Resource Heap Tier: %s", options.ResourceHeapTier);
	LOG_INFO("ROVs Supported: %s", options.ROVsSupported != 0);

	// Create Command Queue
	m_CommandQueue = New<CommandQueueDX12>(this, D3D12_COMMAND_LIST_TYPE_DIRECT);
	if (!m_CommandQueue->Init())
	{
		return false;
	}

	// Create Rendering Main Context
	m_MainContext = New<GPUContextDX12>(this, D3D12_COMMAND_LIST_TYPE_DIRECT);

	// Create desriptors heaps

	// Create root signature


	return GPUDevice::Init();
}

void GPUDeviceDX12::Draw()
{
	
	

}

void GPUDeviceDX12::Dispose()
{

}


GPUDevice* CreateGPUDeviceDX12()
{
	return GPUDeviceDX12::Create();
}


#endif