#pragma once

#include "MaterialBase.h"
#include "Engine/Graphics/GPUConstantBuffer.h"

namespace DawnEngine
{
	class PBRMaterial : public MaterialBase
	{
	public:

		PBRMaterial(Color color);

		bool InitGPUResource() override;

		void Draw(GPUContext* context) override;

	public:

		TextureData* AlbedoTexture;
		TextureData* AOTexture;
		TextureData* MetallicTexture;
		TextureData* NormalTexture;
		TextureData* RoughnessTexture;

		float Metallic;
		float Roughness;

	private:

		PBRMaterialConstants m_ConstantInfo;

		GPUTexture* m_AlbedoTexture;
		GPUTexture* m_NormalTexture;
		GPUTexture* m_MetallicTexture;
		GPUTexture* m_RoughnessTexture;
		GPUTexture* m_AOTexture;

	};
}