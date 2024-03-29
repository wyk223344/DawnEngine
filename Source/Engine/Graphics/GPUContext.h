#pragma once

#include "Engine/Core/Include.h"


namespace DawnEngine
{
	struct Color;
	struct Vector4;
	class GPUDevice;
	class GPUBuffer;
	class GPUTexture;
	class GPUTextureView;
	class GPUResource;
	class GPUPipelineState;
	class GPUConstantBuffer;

	/*
		GPU Context
	*/
	class GPUContext : Object
	{
	public:

		GPUContext(GPUDevice* device);

	public:

		// 开始新的一帧的绘制
		virtual void FrameBegin();

		// 结束此帧绘制，将收集的指令提交到GPU
		virtual void FrameEnd();

	public:

		// 设置视口和裁剪矩形
		void SetViewportAndScissors(float width, float height)
		{
			const Viewport viewport(0.0f, 0.0f, width, height);
			SetViewport(viewport);
			const Rectangle scissorRect(0.0f, 0.0f, width, height);
			SetScissor(scissorRect);
		}

		// 设置视口
		virtual void SetViewport(const Viewport& viewport) = 0;

		// 设置裁剪矩形
		virtual void SetScissor(const Rectangle& scissorRect) = 0;

	public:

		// 用指定的颜色Clear 渲染目标纹理
		virtual void Clear(GPUTextureView* rt, const Color& color) = 0;

		// 清理深度缓冲纹理
		virtual void ClearDepth(GPUTextureView* depthBuffer, float depthValue = 1.0f) = 0;

		// 设置渲染目标
		virtual void SetRenderTarget(GPUTextureView* rt) = 0;

		// 设置渲染目标和深度缓冲区
		virtual void SetRenderTarget(GPUTextureView* rt, GPUTextureView* depthBuffer) = 0;

		// 绑定纹理到着色器资源
		virtual void BindSR(int32 slot, GPUTextureView* view) = 0;

		// 绑定顶点缓冲区, vertex buffer
		virtual void BindVB(GPUBuffer* vertexBuffer) = 0;

		// 绑定索引缓冲区, index buffer
		virtual void BindIB(GPUBuffer* indexBuffer) = 0;

		// 绑定常量缓冲区
		virtual void BindCB(int32 slot, GPUConstantBuffer* cb) = 0;

		// 解绑常量缓冲区
		void UnBindCB(int32 slot) { BindCB(slot, nullptr); }

		// 更新常量缓冲区数据
		virtual void UpdateCB(GPUConstantBuffer* cb, const void* data) = 0;

		// 更新buffer数据
		virtual void UpdateBuffer(GPUBuffer* buffer, const void* data, uint32 size, uint32 offset = 0) = 0;

		// 更新纹理数据
		virtual void UpdateTexture(GPUTexture* texture, int32 arrayIndex, int32 mipIndex, const void* data, uint32 rowPitch, uint32 slicePitch) = 0;

		/// <summary>
		/// 通过索引来绘制实例
		/// </summary>
		/// <param name="indicesCount">索引数量</param>
		/// <param name="instanceCount">实例化技术相关。暂时为1</param>
		/// <param name="startIndex">起始索引</param>
		/// <param name="startVertex">在本次绘制调用读取顶点之前，为每个索引加上此整数值</param>
		/// <param name="startInstance">实例化技术相关，暂时为0</param>
		virtual void DrawIndexedInstanced(uint32 indicesCount, uint32 instanceCount, int32 startIndex = 0, int32 startVertex = 0, int32 startInstance = 0) = 0;

		// 进行全屏绘制
		void DrawFullscreenTriangle();

		// 绘制纹理
		void Draw(GPUTexture* srcRT);

		// 设置PipelineState
		virtual void SetState(GPUPipelineState* state) = 0;

		// 获取当前的PipelineState
		virtual GPUPipelineState* GetState() const = 0;

		// 清理当前状态
		virtual void ClearState() = 0;

		// 提交渲染相关指令
		virtual void FlushState() = 0;

		// 执行渲染相关指令
		virtual void Flush() = 0;

		// 测试函数
		// virtual void DoTestDraw() = 0;

	private:

		GPUDevice* m_Device;
	};

}