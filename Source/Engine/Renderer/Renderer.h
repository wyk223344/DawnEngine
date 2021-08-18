#pragma once


namespace DawnEngine
{
	class GPUContext;
	class GPUTexture;
	class RenderContext;

	class Renderer
	{
	public:
		static void Render(GPUContext* context);

		static RenderContext* GetRenderContext();
	};
}