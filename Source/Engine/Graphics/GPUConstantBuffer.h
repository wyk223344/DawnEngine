#pragma once

#include "Engine/Core/Include.h"
#include "GPUResource.h"

namespace DawnEngine
{
	using namespace Math;

	__declspec(align(256)) struct DefaultMaterialConstants
	{
		Color Color;
	};

	__declspec(align(256)) struct PBRMaterialConstants
	{
		Color Color;
	};

	__declspec(align(256)) struct SkyboxMaterialConstants
	{
		Vector3 CameraPosition;
	};

	__declspec(align(256)) struct MeshConstants
	{
		Matrix4x4 WorldMatrix;
	};

	__declspec(align(256)) struct GlobalConstants
	{
		Matrix4x4 ViewProjMatrix;
	};

	class GPUConstantBuffer : public GPUResource
	{
	public:

		uint32 GetSize() const { return m_Size; }

	protected:

		uint32 m_Size = 0;
	};
}