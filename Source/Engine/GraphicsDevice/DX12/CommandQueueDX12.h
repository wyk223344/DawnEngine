#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Include.h"
#include "IncludeDX12Headers.h"
#include "CommandAllocatorPoolDX12.h"

namespace DawnEngine::DX12
{
	class GPUDeviceDX12;
	class GPUContextDX12;
	class CommandQueueDX12;

	/// <summary>
	/// Wraps a fence object and provides functionality for common operations for GPU/CPU operations synchronization.
	/// </summary>
	class FenceDX12
	{
	public:
		FenceDX12(GPUDeviceDX12* device);

    public:
        uint64 GetCurrentValue() const
        {
            return m_CurrentValue;
        }

        uint64 GetLastSignaledValue() const
        {
            return m_LastSignaledValue;
        }

        uint64 GetLastCompletedValue() const
        {
            return m_LastCompletedValue;
        }

	public:

		bool Init();
		void Release();
		uint64 Signal(CommandQueueDX12* queue);
		void WaitGPU(CommandQueueDX12* queue, uint64 value);
		void WaitCPU(uint64 value);
		bool IsFenceComplete(uint64 value);

	private:
		uint64 m_CurrentValue;
		uint64 m_LastSignaledValue;
		uint64 m_LastCompletedValue;
		HANDLE m_Event;
		ID3D12Fence* m_Fence;
		GPUDeviceDX12* m_Device;
	};


    /// <summary>
    /// GPU commands execution sync point for DirectX 12.
    /// </summary>
    struct SyncPointDX12
    {
        FenceDX12* Fence;
        uint64 Value;

        SyncPointDX12()
            : Fence(nullptr)
            , Value(0)
        {
        }

        SyncPointDX12(FenceDX12* fence, uint64 value)
            : Fence(fence)
            , Value(value)
        {
        }

        SyncPointDX12(const SyncPointDX12& other)
            : Fence(other.Fence)
            , Value(other.Value)
        {
        }

        SyncPointDX12& operator=(const SyncPointDX12& other)
        {
            Fence = other.Fence;
            Value = other.Value;
            return *this;
        }

        bool operator!() const
        {
            return Fence == nullptr;
        }

        bool IsValid() const
        {
            return Fence != nullptr;
        }

        bool IsOpen() const
        {
            return Value == Fence->GetCurrentValue();
        }

        bool IsComplete() const
        {
            return Fence->IsFenceComplete(Value);
        }

        void WaitForCompletion() const
        {
            Fence->WaitCPU(Value);
        }
    };


	class CommandQueueDX12
	{
        friend GPUDeviceDX12;
        friend GPUContextDX12;

    private:
        GPUDeviceDX12* m_Device;
        ID3D12CommandQueue* m_CommandQueue;
        const D3D12_COMMAND_LIST_TYPE m_Type;
        CommandAllocatorPoolDX12 m_AllocatorPool;
        FenceDX12 m_Fence;

    public:

        CommandQueueDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type);

        ~CommandQueueDX12();

        bool IsReady() const
        {
            return m_CommandQueue != nullptr;
        }

        ID3D12CommandQueue* GetCommandQueue() const
        {
            return m_CommandQueue;
        }

        CommandAllocatorPoolDX12& GetAllocatorPool()
        {
            return m_AllocatorPool;
        }

        SyncPointDX12 GetSyncPoint()
        {
            return SyncPointDX12(&m_Fence, m_Fence.GetCurrentValue());
        }

    public:

        // Init resources
        bool Init();

        // Cleanup all stuff
        void Release();

        // Stalls the execution on current thread to wait for the GPU to step over given fence value.
        void WaitForFence(uint64 fenceValue);

        // Stalls the execution on current thread to wait for the GPU to finish it's job.
        void WaitForGPU();

        // Executes a command list.
        uint64 ExecuteCommandList(ID3D12CommandList* list);

        // Requests new clean allocator to use.
        ID3D12CommandAllocator* RequestAllocator();

        // Discards used allocator.
        void DiscardAllocator(uint64 fenceValueForReset, ID3D12CommandAllocator* allocator);
	};
}

#endif