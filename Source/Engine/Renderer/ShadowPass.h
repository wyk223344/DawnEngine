#pragma once


#include "RendererPassBase.h"

namespace DawnEngine
{
	class GPUContext;
	class GPUTexture;
	class RenderContext;
	class LightBase;

	class ShadowPass : public RenderPassBase<ShadowPass>
	{
	public:

		void Init();

		void RenderShadow(RenderContext* renderContext, LightBase* light, GPUTexture* renderTarget);

		void Dispose();
	};
}