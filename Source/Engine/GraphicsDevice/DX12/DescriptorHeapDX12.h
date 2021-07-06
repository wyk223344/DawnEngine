#pragma once


#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/GPUResource.h"
#include "Engine/Core/Include.h"
#include "IncludeDX12Headers.h"

#include <vector>


namespace DawnEngine::DX12
{
	class GPUDeviceDX12;

	/// <summary>
	/// 
	/// </summary>
	class DescriptorHeapWithSlotsDX12 : public GPUResource
	{
	public:

		struct Slot
		{
			DescriptorHeapWithSlotsDX12* Heap = nullptr;
			uint32 Index;

			~Slot()
			{
				assert(Heap == nullptr);
			}

			bool IsValid() const
			{
				return Heap != nullptr;
			}

			D3D12_CPU_DESCRIPTOR_HANDLE CPU() const;
			D3D12_GPU_DESCRIPTOR_HANDLE GPU() const;

			// Creates shader resource view
			void CreateSRV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC* desc = nullptr);

			// Creates render target view
			void CreateRTV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_RENDER_TARGET_VIEW_DESC* desc = nullptr);

			// Creates depth stencil view
			void CreateDSV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_DEPTH_STENCIL_VIEW_DESC* desc = nullptr);

			// Creates unordered access view
			void CreateUAV(GPUDeviceDX12* device, ID3D12Resource* resource, D3D12_UNORDERED_ACCESS_VIEW_DESC* desc = nullptr, ID3D12Resource* counterResource = nullptr);

			// Release
			void Release();
		};

	private:

		GPUDeviceDX12* m_Device;
		ID3D12DescriptorHeap* m_Heap;
		D3D12_CPU_DESCRIPTOR_HANDLE m_BeginCPU;
		D3D12_GPU_DESCRIPTOR_HANDLE m_BeginGPU;
		D3D12_DESCRIPTOR_HEAP_TYPE m_Type;
		uint32 m_IncrementSize;
		uint32 m_DescriptorsCount;
		bool m_ShaderVisible;
		std::vector<uint32> m_Usage;

	public:

		DescriptorHeapWithSlotsDX12(GPUDeviceDX12* device);

		// Get heap
		operator ID3D12DescriptorHeap* () const
		{
			return m_Heap;
		}

		// Get handle to the CPU view at given index
		D3D12_CPU_DESCRIPTOR_HANDLE CPU(uint32 index)
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handle;
			handle.ptr = m_BeginCPU.ptr + (SIZE_T)(index * m_IncrementSize);
			return handle;
		}

		// Get handle to the GPU view at given index
		D3D12_GPU_DESCRIPTOR_HANDLE GPU(uint32 index)
		{
			D3D12_GPU_DESCRIPTOR_HANDLE handle;
			handle.ptr = m_BeginGPU.ptr + index * m_IncrementSize;
			return handle;
		}

		// Create heap data
		bool Create(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 descriptorsCount, bool shaderVisible = false);

		// Tries to find free descriptor slot
		bool TryToGetUnusedSlot(uint32& index);

		// Release descriptor slot
		void ReleaseSlot(uint32 index);

	};

	/// <summary>
	/// Descriptors heap pool for DirectX 12.
	/// </summary>
	class DescriptorHeapPoolDX12
	{
	private:

		GPUDeviceDX12* m_Device;
		D3D12_DESCRIPTOR_HEAP_TYPE m_Type;
		uint32 m_DescriptorsCount;
		bool m_ShaderVisible;
		std::vector<DescriptorHeapWithSlotsDX12*> m_Heaps;

	public:
		
		DescriptorHeapPoolDX12(GPUDeviceDX12* device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 descriptorsCount, bool shaderVisible);

		void Init();

		void AllocateSlot(DescriptorHeapWithSlotsDX12*& heap, uint32& slot);

		void ReleaseGPU();
	};

	class DescriptorHeapRingBufferDX12 : public GPUResource
	{
	public:

		struct Allocation
		{
			D3D12_CPU_DESCRIPTOR_HANDLE CPU;
			D3D12_GPU_DESCRIPTOR_HANDLE GPU;
		};

	private:

		GPUDeviceDX12* m_Device;
		ID3D12DescriptorHeap* m_Heap;
		D3D12_CPU_DESCRIPTOR_HANDLE m_BeginCPU;
		D3D12_GPU_DESCRIPTOR_HANDLE m_BeginGPU;
		D3D12_DESCRIPTOR_HEAP_TYPE m_Type;
		uint32 m_IncrementSize;
		uint32 m_DescriptorsCount;
		uint32 m_FirstFree;
		bool m_ShaderVisible;

	public:

		DescriptorHeapRingBufferDX12(GPUDeviceDX12* device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 descriptorsCount, bool shaderVisible);

	public:

		ID3D12DescriptorHeap* GetHeap() const { return m_Heap; }

	public:

		bool Init();

		Allocation AllocateTable(uint32 numDesc);

	protected:

		void OnReleaseGPU() override;
	};
}

#endif