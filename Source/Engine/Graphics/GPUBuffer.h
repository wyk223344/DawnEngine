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

		// �Ƿ��ѱ���ʼ����
		bool IsAllocated() const { return m_Desc.Size > 0; }

		// �Ƿ�����ɫ����Դ
		bool IsShaderResource() const { return m_Desc.IsShaderResource(); }

		// �Ƿ������������Դ
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