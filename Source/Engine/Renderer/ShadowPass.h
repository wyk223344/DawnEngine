#pragma once


#include "RendererPassBase.h"

namespace DawnEngine
{
	class GPUContext;
	class GPUTexture;
	class RenderContext;
	class DirectionalLight;
	class ShadowMaterial;

	class ShadowPass : public RenderPassBase<ShadowPass>
	{
	public:

		void Init();

		void RenderShadow(RenderContext* renderContext, DirectionalLight* light, GPUTexture* renderTarget);

		void Dispose();

	private:

		ShadowMaterial* m_ShadowMaterial;

	};
}