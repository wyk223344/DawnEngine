#pragma once

#include "Engine/Core/Include.h"
#include "GPUResource.h"

namespace DawnEngine
{
	class GPUConstantBuffer : public GPUResource
	{
	public:

		uint32 GetSize() const { return m_Size; }

	protected:

		uint32 m_Size = 0;
	};
}