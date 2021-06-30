#pragma once

#include "GPUResource.h"
#include "GPUBufferDescription.h"

namespace DawnEngine
{
	class GPUBuffer : public GPUResource
	{
	public:

		GPUBuffer()
		{
			m_Desc.Size = 0;
		}

	public:

		// 是否已被初始化过
		bool IsAllocated() const { return m_Desc.Size > 0; }

		// 是否是着色器资源
		bool IsShaderResource() const { return m_Desc.IsShaderResource(); }

		// 是否是无序访问资源
		bool IsUnorderedAccess() const { return m_Desc.IsUnorderedAccess(); }

		// 
		uint32 GetStride() const { return m_Desc.Stride; }

		// 
		uint64 GetSizeInBytes() const { return m_MemoryUsage; }

	public:

		bool Init(const GPUBufferDescription& desc);

	protected:

		virtual bool OnInit() = 0;

	protected:

		void OnReleaseGPU() override;

	protected:

		GPUBufferDescription m_Desc;
	};
}