#pragma once

#include "Engine/Core/Include.h"
#include "GPUResource.h"

namespace DawnEngine
{
	using namespace Math;

	struct LightDataConstant
	{
		Matrix4x4 ViewProjMatrix;
		Vector3 Direction;
		Color Color;
	};

	__declspec(align(256)) struct GlobalConstants
	{
		Matrix4x4 ViewProjMatrix;
		Vector3 CameraPosition;
		int32 DirectionalLightCount;
		LightDataConstant LightDatas[4];
	};

	__declspec(align(256)) struct MeshConstants
	{
		Matrix4x4 WorldMatrix;
	};

	__declspec(align(256)) struct DefaultMaterialConstants
	{
		Color Color;
	};

	__declspec(align(256)) struct PBRMaterialConstants
	{
		Color Color;
		float Metallic;
		float Roughness;
	};

	__declspec(align(256)) struct SkyboxMaterialConstants
	{
		Vector3 CameraPosition;
	};

	class GPUConstantBuffer : public GPUResource
	{
	public:

		uint32 GetSize() const { return m_Size; }

	protected:

		uint32 m_Size = 0;
	};
}