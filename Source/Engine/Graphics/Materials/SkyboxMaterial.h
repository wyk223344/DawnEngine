#pragma once


#include "MaterialBase.h"
#include "Engine/Graphics/GPUConstantBuffer.h"

namespace DawnEngine
{
	class GPUTexture;
	class TextureData;
	class GPUPipelineState;
	class Mesh;
	class RenderContext;

	class SkyboxMaterial : public MaterialBase
	{
	public:

		SkyboxMaterial();

		bool InitGPUResource() override;

		void Draw(GPUContext* context) override;

		void PreIntegrateCubemap(RenderContext* renderContext, Mesh* skyMesh);

	public:

		TextureData* CubeMap;

	private:

		GPUTexture* m_GPUTexture;

		SkyboxMaterialConstants m_ConstantInfo;

		GPUTexture* m_IrradianceTexture;
		GPUPipelineState* m_IrradiancePSO;
		
		GPUTexture* m_PrefilterTexture;
		GPUPipelineState* m_PrefilterPSO;

		bool m_IsInit = false;
	};
}