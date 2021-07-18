
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
	ComPtr<ID3D12Debug> debugController;
	ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
	debugController->EnableDebugLayer();

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

	// Create empty views
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.PlaneSlice = 0;
		srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
		Null_SRV.CreateSRV(this, nullptr, &srvDesc);
	}

	// Create root signature
	{
		// descriptor tables
		D3D12_DESCRIPTOR_RANGE r[1];
		{
			D3D12_DESCRIPTOR_RANGE& range = r[0];
			range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			range.NumDescriptors = DX12_MAX_SR_BINDED;
			range.BaseShaderRegister = 0;
			range.RegisterSpace = 0;
			range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		}
		
		// root parameters
		D3D12_ROOT_PARAMETER rootParameters[3];
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
		{
			D3D12_ROOT_PARAMETER& rootParam = rootParameters[2];
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			rootParam.DescriptorTable.NumDescriptorRanges = 1;
			rootParam.DescriptorTable.pDescriptorRanges = &r[0];
		}

		// Static Samplers
		D3D12_STATIC_SAMPLER_DESC staticSamplers[6];
		// Linear Clamp
		{
			staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[0].MipLODBias = 0.0f;
			staticSamplers[0].MaxAnisotropy = 1;
			staticSamplers[0].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			staticSamplers[0].MinLOD = 0;
			staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
			staticSamplers[0].ShaderRegister = 0;
			staticSamplers[0].RegisterSpace = 0;
			staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		}
		// Point Clamp
		{
			staticSamplers[1].Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			staticSamplers[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[1].MipLODBias = 0.0f;
			staticSamplers[1].MaxAnisotropy = 1;
			staticSamplers[1].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			staticSamplers[1].MinLOD = 0;
			staticSamplers[1].MaxLOD = D3D12_FLOAT32_MAX;
			staticSamplers[1].ShaderRegister = 1;
			staticSamplers[1].RegisterSpace = 0;
			staticSamplers[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		}
		// Linear Wrap
		{
			staticSamplers[2].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			staticSamplers[2].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[2].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[2].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[2].MipLODBias = 0.0f;
			staticSamplers[2].MaxAnisotropy = 1;
			staticSamplers[2].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			staticSamplers[2].MinLOD = 0;
			staticSamplers[2].MaxLOD = D3D12_FLOAT32_MAX;
			staticSamplers[2].ShaderRegister = 2;
			staticSamplers[2].RegisterSpace = 0;
			staticSamplers[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		}
		// Point Wrap
		{
			staticSamplers[3].Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			staticSamplers[3].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[3].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[3].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[3].MipLODBias = 0.0f;
			staticSamplers[3].MaxAnisotropy = 1;
			staticSamplers[3].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			staticSamplers[3].MinLOD = 0;
			staticSamplers[3].MaxLOD = D3D12_FLOAT32_MAX;
			staticSamplers[3].ShaderRegister = 3;
			staticSamplers[3].RegisterSpace = 0;
			staticSamplers[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		}
		// Shadow
		{
			staticSamplers[4].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
			staticSamplers[4].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[4].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[4].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[4].MipLODBias = 0.0f;
			staticSamplers[4].MaxAnisotropy = 1;
			staticSamplers[4].ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			staticSamplers[4].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			staticSamplers[4].MinLOD = 0;
			staticSamplers[4].MaxLOD = D3D12_FLOAT32_MAX;
			staticSamplers[4].ShaderRegister = 4;
			staticSamplers[4].RegisterSpace = 0;
			staticSamplers[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		}
		// Shadow PCF
		{
			staticSamplers[5].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
			staticSamplers[5].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[5].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[5].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			staticSamplers[5].MipLODBias = 0.0f;
			staticSamplers[5].MaxAnisotropy = 1;
			staticSamplers[5].ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			staticSamplers[5].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			staticSamplers[5].MinLOD = 0;
			staticSamplers[5].MaxLOD = D3D12_FLOAT32_MAX;
			staticSamplers[5].ShaderRegister = 5;
			staticSamplers[5].RegisterSpace = 0;
			staticSamplers[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		}

		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.NumParameters = ARRAY_COUNT(rootParameters);
		rootSignatureDesc.pParameters = rootParameters;
		rootSignatureDesc.NumStaticSamplers = ARRAY_COUNT(staticSamplers);
		rootSignatureDesc.pStaticSamplers = staticSamplers;
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

GPUTexture* GPUDeviceDX12::CreateTexture()
{
	return New<GPUTextureDX12>(this);
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