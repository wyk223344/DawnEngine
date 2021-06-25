#if GRAPHICS_API_DIRECTX12

#include "CommandQueueDX12.h"
#include "GPUDeviceDX12.h"

using namespace DawnEngine::DX12;

#pragma region FenceDX12

FenceDX12::FenceDX12(GPUDeviceDX12* device)
	: m_CurrentValue(1)
	, m_LastSignaledValue(0)
	, m_LastCompletedValue(0)
	, m_Device(device)
	, m_Fence(nullptr)
	, m_Event(nullptr)
{
}

bool FenceDX12::Init()
{
	ThrowIfFailed(m_Device->GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence)));
	m_Event = CreateEvent(nullptr, false, false, nullptr);
	assert(m_Event != INVALID_HANDLE_VALUE);
	return true;
}

void FenceDX12::Release()
{
	CloseHandle(m_Event);
	m_Event = nullptr;
	m_Fence->Release();
	m_Fence = nullptr;
}

uint64 FenceDX12::Signal(CommandQueueDX12* queue)
{
	assert(m_LastSignaledValue != m_CurrentValue);

	// Insert signal into command queue
	ThrowIfFailed(queue->GetCommandQueue()->Signal(m_Fence, m_CurrentValue));

	// Update state
	m_LastSignaledValue = m_CurrentValue;
	m_LastCompletedValue = m_Fence->GetCompletedValue();
	m_CurrentValue++;

	return m_LastSignaledValue;
}

void FenceDX12::WaitGPU(CommandQueueDX12* queue, uint64 value)
{
	ThrowIfFailed(queue->GetCommandQueue()->Wait(m_Fence, value));
}

void FenceDX12::WaitCPU(uint64 value)
{
	if (IsFenceComplete(value))
	{
		return;
	}
	// Fire event when GPU hits current fence.  
	ThrowIfFailed(m_Fence->SetEventOnCompletion(value, m_Event));
	WaitForSingleObject(m_Event, INFINITE);
	m_LastCompletedValue = m_Fence->GetCompletedValue();
}

bool FenceDX12::IsFenceComplete(uint64 value)
{
	assert(value <= m_CurrentValue);
	
	if (value > m_LastCompletedValue)
	{
		m_LastCompletedValue = m_Fence->GetCompletedValue();
	}
	return value <= m_LastCompletedValue;
}

#pragma endregion

#pragma region CommandQueueDX12

CommandQueueDX12::CommandQueueDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type)
	: m_Device(device)
	, m_CommandQueue(nullptr)
	, m_Type(type)
	, m_AllocatorPool(device, type)
	, m_Fence(device)
{
}

CommandQueueDX12::~CommandQueueDX12()
{
	Release();
}

// Init resources
bool CommandQueueDX12::Init()
{
	/*assert(m_Device != nullptr);
	assert(!IsReady());
	assert(m_AllocatorPool.Size() == 0);*/
	LOG_INFO("CommandQueueDX12 Start Init!");
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = m_Type;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.NodeMask = 0;
	ThrowIfFailed(m_Device->GetDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_CommandQueue)));

	if (!m_Fence.Init())
	{
		return false;
	}

	assert(IsReady());

	return true;
}

// Cleanup all stuff
void CommandQueueDX12::Release()
{
	if (!IsReady())
	{
		return;
	}
	m_AllocatorPool.Release();
	m_Fence.Release();
	m_CommandQueue->Release();
	m_CommandQueue = nullptr;
}

// Stalls the execution on current thread to wait for the GPU to step over given fence value.
void CommandQueueDX12::WaitForFence(uint64 fenceValue)
{
	m_Fence.WaitCPU(fenceValue);
}

// Stalls the execution on current thread to wait for the GPU to finish it's job.
void CommandQueueDX12::WaitForGPU()
{
	const uint64 value = m_Fence.Signal(this);
	m_Fence.WaitCPU(value);
}

// Executes a command list.
uint64 CommandQueueDX12::ExecuteCommandList(ID3D12CommandList* list)
{
	ThrowIfFailed((static_cast<ID3D12GraphicsCommandList*>(list))->Close());

	m_CommandQueue->ExecuteCommandLists(1, &list);

	return m_Fence.Signal(this);
}

// Requests new clean allocator to use.
ID3D12CommandAllocator* CommandQueueDX12::RequestAllocator()
{
	const uint64 completedFence = m_Fence.GetLastCompletedValue();
	return m_AllocatorPool.RequestAllocator(completedFence);
}

// Discards used allocator.
void CommandQueueDX12::DiscardAllocator(uint64 fenceValueForReset, ID3D12CommandAllocator* allocator)
{
	m_AllocatorPool.DiscardAllocator(fenceValueForReset, allocator);
}

#pragma endregion


#endif