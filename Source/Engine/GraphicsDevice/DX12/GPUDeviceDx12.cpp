
#if GRAPHICS_API_DIRECTX12

#include "Engine/Engine/Engine.h"
#include "Engine/Core/Include.h"
#include "GPUDeviceDX12.h"
#include "GPUContextDX12.h"
#include "GPUBufferDX12.h"
#include "GPUShaderDX12.h"
#include "GPUConstantBufferDX12.h"
#include "UploadBufferDX12.h"
#include "CommandQueueDX12.h"
#include "GPUSwapChainDX12.h"
#include "GPUPipelineStateDX12.h"
#include "DescriptorHeapDX12.h"
#include "IncludeDX12Headers.h"

using namespace DawnEngine::DX12;
using namespace DawnEngine;
using Microsoft::WRL::ComPtr;

GPUDevice* GPUDeviceDX12::Create()
{
	GPUDeviceDX12* device = New<GPUDeviceDX12>();
	if (!device->Init())
	{
		return nullptr;
	}
	return device;
}

GPUDeviceDX12::GPUDeviceDX12()
	: m_Device(nullptr)
	, m_FactoryDXGI(nullptr)
	, m_RootSignature(nullptr)
	, m_GraphicsQueue(nullptr)
	, m_MainContext(nullptr)
	, Heap_CBV_SRV_UAV(this, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 4 * 1024, false)
	, Heap_RTV(this, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 1 * 1024, false)
	, Heap_DSV(this, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 64, false)
	, RingHeap_CBV_SRV_UAV(this, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 64 * 1024, true)
{
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

	// Create Command Queue
	m_GraphicsQueue = New<CommandQueueDX12>(this, D3D12_COMMAND_LIST_TYPE_DIRECT);
	if (!m_GraphicsQueue->Init())
	{
		return false;
	}

	// Create Rendering Main Context
	m_MainContext = New<GPUContextDX12>(this, D3D12_COMMAND_LIST_TYPE_DIRECT);

	// Create desriptors heaps
	Heap_CBV_SRV_UAV.Init();
	Heap_RTV.Init();
	Heap_DSV.Init();
	if (!RingHeap_CBV_SRV_UAV.Init())
	{
		return false;
	}

	// Create root signature
	{
		// root parameters
		D3D12_ROOT_PARAMETER rootParameters[2];
		{
			D3D12_ROOT_PARAMETER& rootParam = rootParameters[0];
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			rootParam.Descriptor.ShaderRegister = 0;
			rootParam.Descriptor.RegisterSpace = 0;
		}
		{
			D3D12_ROOT_PARAMETER& rootParam = rootParameters[1];
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			rootParam.Descriptor.ShaderRegister = 1;
			rootParam.Descriptor.RegisterSpace = 0;
		}

		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.NumParameters = ARRAY_COUNT(rootParameters);
		rootSignatureDesc.pParameters = rootParameters;
		rootSignatureDesc.NumStaticSamplers = 0;
		rootSignatureDesc.pStaticSamplers = nullptr;
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;
		ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		ThrowIfFailed(m_Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_RootSignature)));
	}

	// Upload buffer
	UploadBuffer = New<UploadBufferDX12>(this);

	LOG_INFO("Finish Init GPUDeviceDX12");

	return GPUDevice::Init();
}

void GPUDeviceDX12::DrawBegin()
{
	GPUDevice::DrawBegin();
	UploadBuffer->BeginGeneration(DawnEngine::Engine::FrameCount);
}

void GPUDeviceDX12::Dispose()
{

}

GPUSwapChain* GPUDeviceDX12::CreateSwapChain(Window* window)
{
	return New<GPUSwapChainDX12>(this, window);
}

GPUBuffer* GPUDeviceDX12::CreateBuffer()
{
	return New<GPUBufferDX12>(this);
}

GPUShader* GPUDeviceDX12::CreateShader()
{
	return New<GPUShaderDX12>(this);
}

GPUPipelineState* GPUDeviceDX12::CreatePipelineState()
{
	return New<GPUPipelineStateDX12>(this);
}

GPUConstantBuffer* GPUDeviceDX12::CreateConstantBuffer(uint32 size)
{
	return New<GPUConstantBufferDX12>(this, size);
}

GPUDevice* CreateGPUDeviceDX12()
{
	return GPUDeviceDX12::Create();
}


#endif