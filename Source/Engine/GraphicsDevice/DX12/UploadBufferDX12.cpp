#if GRAPHICS_API_DIRECTX12

#include "GPUResourceDX12.h"
#include "UploadBufferDX12.h"
#include "GPUDeviceDX12.h"
#include "GPUContextDX12.h"
#include "GPUTextureDX12.h"

using namespace DawnEngine;
using namespace DawnEngine::DX12;

#pragma region UploadBufferPageDX12

UploadBufferPageDX12::UploadBufferPageDX12(GPUDeviceDX12* device, uint64 size)
	: GPUResourceDX12(device)
	, LastGen(0)
	, CPUAddress(nullptr)
	, GPUAddress(0)
	, Size(size)
{
    // Create page buffer
    D3D12_HEAP_PROPERTIES heapProperties;
    heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    D3D12_RESOURCE_DESC resourceDesc;
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Alignment = 0;
    resourceDesc.Width = size;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    ID3D12Resource* resource;
    ThrowIfFailed(m_Device->GetDevice()->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&resource)));
    
    InitResource(resource, D3D12_RESOURCE_STATE_GENERIC_READ);
    GPUAddress = resource->GetGPUVirtualAddress();
    ThrowIfFailed(resource->Map(0, nullptr, &CPUAddress));
}

void UploadBufferPageDX12::OnReleaseGPU()
{
    if (m_Resource && CPUAddress)
    {
        m_Resource->Unmap(0, nullptr);
    }
    ReleaseResource();
}

#pragma endregion


#pragma region UploadBufferDX12

UploadBufferDX12::UploadBufferDX12(GPUDeviceDX12* device)
    : m_Device(device)
    , m_CurrentPage(nullptr)
    , m_CurrentOffset(0)
    , m_CurrentGeneration(0)
{
}

UploadBufferDX12::~UploadBufferDX12()
{
    for (auto page : m_UsedPages)
    {
        page->ReleaseGPU();
        Delete(page);
    }
    for (auto page : m_FreePages)
    {
        page->ReleaseGPU();
        Delete(page);
    }
}

DynamicAllocation UploadBufferDX12::Allocate(uint64 size, uint64 align)
{
    const uint64 alignmentMask = align - 1;
    assert((alignmentMask & align) == 0);

    const bool useDefaultSize = size <= DX12_DEFAULT_UPLOAD_PAGE_SIZE;
    const uint64 pageSize = useDefaultSize ? DX12_DEFAULT_UPLOAD_PAGE_SIZE : size;
    const uint64 alignedSize = Math::AlignUpWithMask(size, alignmentMask);

    m_CurrentOffset = Math::AlignUpWithMask(m_CurrentOffset, alignmentMask);

    if (m_CurrentPage && m_CurrentOffset + alignedSize > m_CurrentPage->Size)
    {
        m_CurrentPage = nullptr;
    }

    if (m_CurrentPage == nullptr)
    {
        m_CurrentPage = requestPage(pageSize);
        m_CurrentOffset = 0;
    }

    m_CurrentPage->LastGen = m_CurrentGeneration;

    const DynamicAllocation result(static_cast<byte*>(m_CurrentPage->CPUAddress) + m_CurrentOffset, m_CurrentOffset, size, m_CurrentPage->GPUAddress + m_CurrentOffset, m_CurrentPage, m_CurrentGeneration);

    m_CurrentOffset += size;

    //LOG_WARNING("[UploadBufferDX12] Allocate CurPage CPUAddress %u Offset %u Size %u PageSize %u AlignSize %u", m_CurrentPage->CPUAddress, m_CurrentOffset, size, m_CurrentPage->Size, alignedSize);

    return result;
}

// 数据通过上传缓冲区上传到GPU，再拷到指定Buffer区域
bool UploadBufferDX12::UploadBuffer(GPUContextDX12* context, ID3D12Resource* buffer, uint32 bufferOffset, const void* data, uint64 size)
{
    const DynamicAllocation allocation = Allocate(size, 4);
    if (allocation.IsInvalid())
    {
        return false;
    }
    Platform::MemoryCopy(allocation.CPUAddress, data, static_cast<size_t>(size));
    context->GetCommandList()->CopyBufferRegion(buffer, bufferOffset, allocation.Page->GetResource(), allocation.Offset, size);
    return true;
}

bool UploadBufferDX12::UploadTexture(GPUContextDX12* context, ID3D12Resource* texture, const void* srcData, uint32 srcRowPitch, uint32 srcSlicePitch, int32 mipIndex, int32 arrayIndex)
{
    return true;
}

void UploadBufferDX12::BeginGeneration(uint64 generation)
{
    for (int32 i = m_UsedPages.size() - 1; i >= 0; i--)
    {
        auto page = m_UsedPages[i];
        if (page == m_CurrentPage)
        {
            continue;
        }
        if (page->LastGen + DX12_UPLOAD_PAGE_GEN_TIMEOUT < generation)
        {
            m_UsedPages.erase(m_UsedPages.begin() + i);
            m_FreePages.push_back(page);
        }
    }
    for (int32 i = m_FreePages.size() - 1; i >= 0; i--)
    {
        auto page = m_FreePages[i];
        if (page->LastGen + DX12_UPLOAD_PAGE_GEN_TIMEOUT + DX12_UPLOAD_PAGE_NOT_USED_FRAME_TIMEOUT < generation)
        {
            m_FreePages.erase(m_FreePages.begin() + i);
            page->ReleaseGPU();
            Delete(page);
        }
    }
}

UploadBufferPageDX12* UploadBufferDX12::requestPage(uint64 size)
{
    int32 freePageIndex = -1;
    for (int i = 0; i < m_FreePages.size(); i++)
    {
        if (m_FreePages[i]->Size == size)
        {
            freePageIndex = i;
            break;
        }
    }

    UploadBufferPageDX12* page;
    if (freePageIndex == -1)
    {
        page = New<UploadBufferPageDX12>(m_Device, size);
    }
    else
    {
        page = m_FreePages[freePageIndex];
        m_FreePages.erase(m_FreePages.begin() + freePageIndex);
    }
    m_UsedPages.push_back(page);
    return page;
}


#pragma endregion

#endif