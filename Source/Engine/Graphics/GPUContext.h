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
	class GPUContext : Object
	{
	public:

		// ��ʼ�µ�һ֡�Ļ���
		virtual void FrameBegin();

		// ������֡���ƣ����ռ���ָ���ύ��GPU
		virtual void FrameEnd();

	public:

		// �����ӿںͲü�����
		void SetViewportAndScissors(float width, float height)
		{
			const Math::Viewport viewport(0.0f, 0.0f, width, height);
			SetViewport(viewport);
			const Math::Rectangle scissorRect(0.0f, 0.0f, width, height);
			SetScissor(scissorRect);
		}

		// �����ӿ�
		virtual void SetViewport(const Math::Viewport& viewport) = 0;

		// ���òü�����
		virtual void SetScissor(const Math::Rectangle& scissorRect) = 0;

	public:

		// ��ָ������ɫClear����
		virtual void Clear(GPUTextureView* rt, const Color& color) = 0;

		// ������ȾĿ��
		virtual void SetRenderTarget(GPUTextureView* rt) = 0;

		// �󶨶��㻺����, vertex buffer
		virtual void BindVB(const Span<GPUBuffer*>& vertexBuffers, const uint32* vertexBuffersOffsets) = 0;

		// ������������, index buffer
		virtual void BindIB(GPUBuffer* indexBuffer) = 0;

		/// <summary>
		/// ͨ������������ʵ��
		/// </summary>
		/// <param name="indicesCount">��������</param>
		/// <param name="instanceCount">ʵ����������ء���ʱΪ1</param>
		/// <param name="startIndex">��ʼ����</param>
		/// <param name="startVertex">�ڱ��λ��Ƶ��ö�ȡ����֮ǰ��Ϊÿ���������ϴ�����ֵ</param>
		/// <param name="startInstance">ʵ����������أ���ʱΪ0</param>
		virtual void DrawIndexedInstanced(uint32 indicesCount, uint32 instanceCount, int32 startIndex = 0, int32 startVertex = 0, int32 startInstance = 0) = 0;

		// ����PipelineState
		virtual void SetState(GPUPipelineState* state) = 0;

		// ��ȡ��ǰ��PipelineState
		virtual GPUPipelineState* GetState() const = 0;

		// ����ǰ״̬
		virtual void ClearState() = 0;

		// �ύ��Ⱦ���ָ��
		virtual void FlushState() = 0;

		// ִ����Ⱦ���ָ��
		virtual void Flush() = 0;
	};

}