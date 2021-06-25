#pragma once

#include "Engine/Core/Include.h"


namespace DawnEngine
{
	struct Color;
	struct Vector4;
	class GPUDevice;
	class GPUBuffer;
	class GPUBufferView;
	class GPUTexture;
	class GPUTextureView;
	class GPUResource;
	class GPUResourceView;
	class GPUPipelineState;

	/*
		GPU Context
	*/
	class GPUContext
	{
	public:

		// 开始新的一帧的绘制
		virtual void FrameBegin();

		// 结束此帧绘制，将收集的指令提交到GPU
		virtual void FrameEnd();

	public:

		void SetViewportAndScissors(float width, float height)
		{
			const Math::Viewport viewport(0.0f, 0.0f, width, height);
			SetViewport(viewport);
			const Math::Rectangle scissorRect(0.0f, 0.0f, width, height);
			SetScissor(scissorRect);
		}

		virtual void SetViewport(const Math::Viewport& viewport) = 0;

		virtual void SetScissor(const Math::Rectangle& scissorRect) = 0;

	public:

		virtual void Clear(GPUTextureView* rt, const Color& color) = 0;

		virtual void SetRenderTarget(GPUTextureView* rt) = 0;



		virtual void BindIB(GPUBuffer* indexBuffer) = 0;

		virtual void DrawIndexedInstanced(uint32 indicesCount, uint32 instanceCount, int32 startInstance = 0, int32 startVertex = 0, int32 startIndex = 0) = 0;

		virtual void SetState(GPUPipelineState* state) = 0;

		virtual GPUPipelineState* GetState() const = 0;

		virtual void ClearState() = 0;

		virtual void FlushState() = 0;

		virtual void Flush() = 0;
	};

}