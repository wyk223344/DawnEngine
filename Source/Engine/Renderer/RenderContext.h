#pragma once

#include <vector>
#include "Engine/Core/Include.h"
#include "Engine/Graphics/GPUConstantBuffer.h"

namespace DawnEngine
{
	class DirectionalLight;
	class GPUTexture;
	class Mesh;
	class MaterialBase;

	struct DrawCall
	{
		Mesh* Mesh;
		MaterialBase* Material;
		Math::Matrix4x4 WorldMatrix;
	};

	struct LightSettings
	{
		float SunLightIntensity;
		Math::Vector3 SunLightDirection;
		Color SunLightColor;
		float IBLIntensity;
		float IBLRotation;
	};

	struct CameraSettings
	{

	};

	struct PostProcessSettings
	{

	};

	struct RenderSettings
	{
		LightSettings Light;
		CameraSettings Camera;
		PostProcessSettings PostProcess;
	};

	class RenderContext
	{
	public:

		// 初始化
		void Init(int32 width, int32 height);

		// 收集渲染所需数据
		void BeforeDraw();

	public:

		int32 Width;
		int32 Height;

		RenderSettings Settings;

		GPUTexture* ForwardPassRT;
		GPUTexture* DepthTexture;

		GPUTexture* ShadowTexture;

		GlobalConstants GlobalConstant;
		MeshConstants MeshConstant;

		GPUConstantBuffer* GlobalConstantBuffer;
		GPUConstantBuffer* MeshConstantBuffer;

		std::vector<DirectionalLight*> DirectionalLightList;

		std::vector<DrawCall> DrawCallList;

		Math::Matrix4x4 CameraViewProjMatrix;

	};
}