#pragma once


#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Include.h"
#include "IncludeDX12Headers.h"
#include "GPUResourceDX12.h"

#include <vector>

#define DX12_DEFAULT_UPLOAD_PAGE_SIZE (4 * 1014 * 1024) // 4 MB

// Upload buffer generations timeout to dispose
#define DX12_UPLOAD_PAGE_GEN_TIMEOUT DX12_BACK_BUFFER_COUNT

// Upload buffer pages that are not used for a few frames are disposed
#define DX12_UPLOAD_PAGE_NOT_USED_FRAME_TIMEOUT 8


namespace DawnEngine::DX12
{
	class GPUDeviceDX12;
	class GPUContextDX12;
	class GPUTextureDX12;

	class UploadBufferPageDX12 : public GPUResourceDX12<GPUResource>, public GPUResourceOwnerDX12
	{
	public:

		UploadBufferPageDX12(GPUDeviceDX12* device, uint64 size);

	protected:

		void OnReleaseGPU() override;

	public:

		uint64 LastGen;

		void* CPUAddress;

		D3D12_GPU_VIRTUAL_ADDRESS GPUAddress;

		uint64 Size;

	};

	struct DynamicAllocation
	{
		void* CPUAddress;

		uint64 Offset;

		uint64 Size;

		D3D12_GPU_VIRTUAL_ADDRESS GPUAddress;

		UploadBufferPageDX12* Page;

		uint64 Generation;

		DynamicAllocation()
			: CPUAddress(nullptr)
			, Offset(0)
			, Size(0)
			, GPUAddress(0)
			, Page(nullptr)
			, Generation(0)
		{
		}

		DynamicAllocation(void* address, uint64 offset, uint64 size, D3D12_GPU_VIRTUAL_ADDRESS gpuAddress, UploadBufferPageDX12* page, uint64 generation)
			: CPUAddress(address)
			, Offset(offset)
			, Size(size)
			, GPUAddress(gpuAddress)
			, Page(page)
			, Generation(generation)
		{
		}

		bool IsInvalid() const
		{
			return CPUAddress == nullptr || Size == 0 || Page == nullptr;
		}
	};


	class UploadBufferDX12 : Object
	{
	public:

		UploadBufferDX12(GPUDeviceDX12* device);

		~UploadBufferDX12();

	public:

		uint64 GetCurrentGeneration() const { return m_CurrentGeneration; }

		DynamicAllocation Allocate(uint64 size, uint64 align);

		bool UploadBuffer(GPUContextDX12* context, ID3D12Resource* buffer, uint32 bufferOffset, const void* data, uint64 size);

		bool UploadTexture(GPUContextDX12* context, ID3D12Resource* texture, const void* srcData, uint32 srcRowPitch, uint32 srcSlicePitch, int32 mipIndex, int32 arrayIndex);
	
		void BeginGeneration(uint64 generation);

	private:

		UploadBufferPageDX12* requestPage(uint64 size);

	private:

		GPUDeviceDX12* m_Device;
		UploadBufferPageDX12* m_CurrentPage;
		uint64 m_CurrentOffset;
		uint64 m_CurrentGeneration;

		std::vector<UploadBufferPageDX12*> m_FreePages;
		std::vector<UploadBufferPageDX12*> m_UsedPages;

	};
}


#endif