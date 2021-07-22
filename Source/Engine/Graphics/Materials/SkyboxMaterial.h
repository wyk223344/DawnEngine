#pragma once


#include "MaterialBase.h"
#include "Engine/Graphics/GPUConstantBuffer.h"

namespace DawnEngine
{
	class GPUTexture;
	class TextureData;

	class SkyboxMaterial : public MaterialBase
	{
	public:

		SkyboxMaterial();

		bool InitGPUResource() override;

		void Draw(GPUContext* context) override;

	public:

		TextureData* CubeMap;

	private:

		GPUTexture* m_GPUTexture;

		SkyboxMaterialConstants m_ConstantInfo;
	};
}