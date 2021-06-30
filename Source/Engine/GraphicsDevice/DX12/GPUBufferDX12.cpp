#if GRAPHICS_API_DIRECTX12

#include "GPUBufferDX12.h"
#include "GPUDeviceDX12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Graphics/PixelFormatExtensions.h"

using namespace DawnEngine::DX12;


bool GPUBufferDX12::OnInit()
{
	const bool useSRV = IsShaderResource();
	const bool useUAV = IsUnorderedAccess();

    // Create description
    D3D12_RESOURCE_DESC resourceDesc;
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Alignment = 0;
    resourceDesc.Width = m_Desc.Size;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    if (!useSRV)
        resourceDesc.Flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
    if (useUAV)
        resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    // Create allocation description
    D3D12_HEAP_PROPERTIES heapProperties;
    switch (m_Desc.Usage)
    {
    case GPUResourceUsage::StagingUpload:
        heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
        break;
    case GPUResourceUsage::StagingReadback:
        heapProperties.Type = D3D12_HEAP_TYPE_READBACK;
        break;
    default:
        heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
    }
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;

    // Create resource
    ID3D12Resource* resource;
    D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COPY_DEST;
    ThrowIfFailed(m_Device->GetDevice()->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        initialState,
        nullptr,
        IID_PPV_ARGS(&resource)));

    // Set state
    InitResource(resource, initialState);
    m_MemoryUsage = m_Desc.Size;
    int32 numElements = m_Desc.GetElementsCount();

    // Check if set initial data
    if (m_Desc.InitData)
    {
        m_Device->GetMainContext()->UpdateBuffer(this, m_Desc.InitData, m_Desc.Size);
    }

    // Create views
    if (useSRV)
    {
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
        if (m_Desc.Flags & GPUBufferFlags::RawBuffer)
            srvDesc.Format = RenderToolsDX12::ToDxgiFormat(m_Desc.Format);
        else
            srvDesc.Format = RenderToolsDX12::ToDxgiFormat(PixelFormatExtensions::FindShaderResourceFormat(m_Desc.Format, false));
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        srvDesc.Buffer.FirstElement = 0;
        srvDesc.Buffer.NumElements = numElements;
        srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
        if (m_Desc.Flags & GPUBufferFlags::Structured)
        {
            srvDesc.Buffer.StructureByteStride = m_Desc.Stride;
            srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        }
        else
        {
            srvDesc.Buffer.StructureByteStride = 0;
        }
        if (m_Desc.Flags & GPUBufferFlags::RawBuffer)
            srvDesc.Buffer.Flags |= D3D12_BUFFER_SRV_FLAG_RAW;
        SetSRV(&srvDesc);
    }
    if (useUAV)
    {
        D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc;
        uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        uavDesc.Buffer.FirstElement = 0;
        uavDesc.Buffer.StructureByteStride = 0;
        uavDesc.Buffer.CounterOffsetInBytes = 0;
        uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
        uavDesc.Buffer.NumElements = numElements;
        if (m_Desc.Flags & GPUBufferFlags::Structured)
            uavDesc.Buffer.StructureByteStride = m_Desc.Stride;
        if (m_Desc.Flags & GPUBufferFlags::RawBuffer)
            uavDesc.Buffer.Flags |= D3D12_BUFFER_UAV_FLAG_RAW;
        if (m_Desc.Flags & GPUBufferFlags::Structured)
            uavDesc.Format = DXGI_FORMAT_UNKNOWN;
        else
            uavDesc.Format = RenderToolsDX12::ToDxgiFormat(PixelFormatExtensions::FindUnorderedAccessFormat(m_Desc.Format));
        SetUAV(&uavDesc, nullptr);
    }

	return true;
}

void GPUBufferDX12::OnReleaseGPU()
{
	ReleaseView();
	ReleaseResource();
	GPUBuffer::OnReleaseGPU();
}


#endif