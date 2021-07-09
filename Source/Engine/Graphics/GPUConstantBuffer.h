#pragma once

#include "Engine/Core/Include.h"
#include "GPUResource.h"

namespace DawnEngine
{

	__declspec(align(256)) struct MeshConstants
	{
		Math::Matrix4x4 WorldMatrix;
	};

	__declspec(align(256)) struct GlobalConstants
	{
		Math::Matrix4x4 ViewProjMatrix;
	};

	class GPUConstantBuffer : public GPUResource
	{
	public:

		uint32 GetSize() const { return m_Size; }

	protected:

		uint32 m_Size = 0;
	};
}