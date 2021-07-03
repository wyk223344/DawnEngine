#pragma once

#include "Engine/Core/Include.h"
#include "Vertex.h"
#include "MeshData.h"

#include <vector>


namespace DawnEngine
{
	class GPUBuffer;

	class Mesh : public Object
	{
	public:

		Mesh()
			: m_VertexBuffer(nullptr)
			, m_IndexBuffer(nullptr)
		{
		}

		~Mesh()
		{
		}

		bool Init(MeshData& meshData);

		void Release();

		GPUBuffer* GetVertexBuffer() const { return m_VertexBuffer; }

		GPUBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

	private:

		GPUBuffer* m_VertexBuffer;
		GPUBuffer* m_IndexBuffer;

	};
}