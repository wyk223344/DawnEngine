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

	public:

		bool Init(const GPUBufferDescription& desc);

	protected:

		GPUBufferDescription m_Desc;
	};
}