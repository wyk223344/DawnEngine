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

	class RenderContext
	{
	public:

		// ��ʼ��
		void Init(int32 width, int32 height);

		// �ռ���Ⱦ��������
		void BeforeDraw();

	public:

		int32 Width;
		int32 Height;

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