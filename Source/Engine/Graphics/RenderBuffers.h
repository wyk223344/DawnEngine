#pragma once


namespace DawnEngine
{
	class GPUTexture;

	class RenderBuffers
	{
	public:

		GPUTexture* ForwardPassResult;
		GPUTexture* DepthBuffer;
	};
}