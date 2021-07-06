#if GRAPHICS_API_DIRECTX12

#include "DescriptorHeapDX12.h"
#include "GPUDeviceDX12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Core/Include.h"

using namespace DawnEngine::DX12;

#pragma region DescriptorHeapWithSlotsDX12::Slot

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapWithSlotsDX12::Slot::CPU() const
{
    return Heap->CPU(Index);
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapWithSlotsDX12::Slot::GPU() const
{
    return Heap->GPU(Index);
}

void DescriptorHeapWithSlotsDX12::Slot::CreateSRV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC* desc)
{
    if (Heap == nullptr)
        device->Heap_CBV_SRV_UAV.AllocateSlot(Heap, Index);
    device->GetDevice()->CreateShaderResourceView(resource, desc, CPU());
}

void DescriptorHeapWithSlotsDX12::Slot::CreateRTV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_RENDER_TARGET_VIEW_DESC* desc)
{
    if (Heap == nullptr)
        device->Heap_RTV.AllocateSlot(Heap, Index);
    device->GetDevice()->CreateRenderTargetView(resource, desc, CPU());
}

void DescriptorHeapWithSlotsDX12::Slot::CreateDSV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_DEPTH_STENCIL_VIEW_DESC* desc)
{
    if (Heap == nullptr)
        device->Heap_DSV.AllocateSlot(Heap, Index);
    device->GetDevice()->CreateDepthStencilView(resource, desc, CPU());
}

void DescriptorHeapWithSlotsDX12::Slot::CreateUAV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_UNORDERED_ACCESS_VIEW_DESC* desc, ID3D12Resource* counterResource)
{
    if (Heap == nullptr)
        device->Heap_CBV_SRV_UAV.AllocateSlot(Heap, Index);
    device->GetDevice()->CreateUnorderedAccessView(resource, counterResource, desc, CPU());
}

void DescriptorHeapWithSlotsDX12::Slot::Release()
{
    if (Heap)
    {
        Heap->ReleaseSlot(Index);
        Heap = nullptr;
    }
}

#pragma endregion

#pragma region DescriptorHeapWithSlotsDX12

DescriptorHeapWithSlotsDX12::DescriptorHeapWithSlotsDX12(GPUDeviceDX12* device)
    : m_Device(device)
    , m_Heap(nullptr)
    , m_DescriptorsCount(0)
{
}

bool DescriptorHeapWithSlotsDX12::Create(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 descriptorsCount, bool shaderVisible)
{
    // Create description
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    desc.Type = type;
    desc.NumDescriptors = descriptorsCount;
    desc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    desc.NodeMask = 0;

    // Create heap
    const HRESULT result = m_Device->GetDevice()->CreateDescriptorHeap(&desc, __uuidof(ID3D12DescriptorHeap), reinterpret_cast<void**>(&m_Heap));
    ThrowIfFailed(result);

    // Setup
    m_Type = type;
    m_ShaderVisible = shaderVisible;
    m_DescriptorsCount = descriptorsCount;
    m_BeginCPU = m_Heap->GetCPUDescriptorHandleForHeapStart();
    if (shaderVisible)
        m_BeginGPU = m_Heap->GetGPUDescriptorHandleForHeapStart();
    else
        m_BeginGPU.ptr = 0;
    m_IncrementSize = m_Device->GetDevice()->GetDescriptorHandleIncrementSize(desc.Type);

    m_Usage.resize(static_cast<int32>(descriptorsCount / 32));
    return true;
}

bool DescriptorHeapWithSlotsDX12::TryToGetUnusedSlot(uint32& index)
{
    for (int32 i = 0; i < m_Usage.capacity(); i++)
    {
        uint32& value = m_Usage[i];
        if (value != MAX_uint32)
        {
            // TODO: make it better?
            for (int32 bit = 0; bit < 32; bit++)
            {
                const uint32 mask = 1 << bit;
                if ((value & mask) == 0)
                {
                    // Found
                    index = i * 32 + bit;
                    value |= mask;
                    return true;
                }
            }
        }
    }

    return false;
}

void DescriptorHeapWithSlotsDX12::ReleaseSlot(uint32 index)
{
    uint32& value = m_Usage[index / 32];
    const uint32 mask = 1 << (index & 31);
    value &= ~mask;
}

#pragma endregion

#pragma region DescriptorHeapPoolDX12

DescriptorHeapPoolDX12::DescriptorHeapPoolDX12(GPUDeviceDX12* device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 descriptorsCount, bool shaderVisible)
    : m_Device(device)
    , m_Type(type)
    , m_DescriptorsCount(descriptorsCount)
    , m_ShaderVisible(shaderVisible)
{
}

void DescriptorHeapPoolDX12::Init()
{
    auto heap = New<DescriptorHeapWithSlotsDX12>(m_Device);
    if (!heap->Create(m_Type, m_DescriptorsCount, m_ShaderVisible))
    {
        LOG_ERROR("Failed to allocate descriptor heap.");
    }
    m_Heaps.push_back(heap);
}

void DescriptorHeapPoolDX12::AllocateSlot(DescriptorHeapWithSlotsDX12*& heap, uint32& slot)
{
    for (int32 i = 0; i < m_Heaps.size(); i++)
    {
        if (m_Heaps[i]->TryToGetUnusedSlot(slot))
        {
            heap = m_Heaps[i];
            return;
        }
    }

    heap = New<DescriptorHeapWithSlotsDX12>(m_Device);
    if (!heap->Create(m_Type, m_DescriptorsCount, m_ShaderVisible))
    {
        LOG_ERROR("Failed to allocate descriptor heap.");
    }
    m_Heaps.push_back(heap);
    heap->TryToGetUnusedSlot(slot);
}

void DescriptorHeapPoolDX12::ReleaseGPU()
{
    
}

#pragma endregion

#pragma region DescriptorHeapRingBufferDX12

DescriptorHeapRingBufferDX12::DescriptorHeapRingBufferDX12(GPUDeviceDX12* device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 descriptorsCount, bool shaderVisible)
    : m_Device(device)
    , m_Heap(nullptr)
    , m_Type(type)
    , m_DescriptorsCount(descriptorsCount)
    , m_ShaderVisible(shaderVisible)
{
}

bool DescriptorHeapRingBufferDX12::Init()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    desc.Type = m_Type;
    desc.NumDescriptors = m_DescriptorsCount;
    desc.Flags = m_ShaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    desc.NodeMask = 0;

    const HRESULT result = m_Device->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_Heap));
    ThrowIfFailed(result);

    m_FirstFree = 0;
    m_BeginCPU = m_Heap->GetCPUDescriptorHandleForHeapStart();
    if (m_ShaderVisible)
    {
        m_BeginGPU = m_Heap->GetGPUDescriptorHandleForHeapStart();
    }
    else
    {
        m_BeginGPU.ptr = 0;
    }
    m_IncrementSize = m_Device->GetDevice()->GetDescriptorHandleIncrementSize(desc.Type);

    m_MemoryUsage = 1;
    return true;
}

DescriptorHeapRingBufferDX12::Allocation DescriptorHeapRingBufferDX12::AllocateTable(uint32 numDesc)
{
    Allocation result;
    uint32 index = m_FirstFree;
    m_FirstFree += numDesc;
    if (m_FirstFree >= m_DescriptorsCount)
    {
        index = 0;
        m_FirstFree = numDesc;
    }
    result.CPU.ptr = m_BeginCPU.ptr + static_cast<SIZE_T>(index * m_IncrementSize);
    result.GPU.ptr = m_ShaderVisible ? m_BeginGPU.ptr + index * m_IncrementSize : 0;
    return result;
}

void DescriptorHeapRingBufferDX12::OnReleaseGPU()
{
    m_Heap->Release();
    m_Heap = nullptr;
    m_FirstFree = 0;
}

#pragma endregion



#endif