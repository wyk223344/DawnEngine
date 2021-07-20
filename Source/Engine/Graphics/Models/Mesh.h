#pragma once

#include "Engine/Core/Include.h"
#include "Vertex.h"
#include "MeshData.h"

#include <vector>


namespace DawnEngine
{
	class GPUBuffer;
	class GPUContext;

	class Mesh : public Object
	{
	public:

		Mesh()
			: m_VertexBuffer(nullptr)
			, m_IndexBuffer(nullptr)
			, m_IndicesCount(0)
		{
		}

		~Mesh()
		{
		}

		bool Init(MeshData& meshData);

		void Draw(GPUContext* context);

		void Release();

		GPUBuffer* GetVertexBuffer() const { return m_VertexBuffer; }

		GPUBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

		uint32 GetIndicesCount() const { return m_IndicesCount; }

	private:

		GPUBuffer* m_VertexBuffer;
		GPUBuffer* m_IndexBuffer;

		uint32 m_IndicesCount;

	};
}