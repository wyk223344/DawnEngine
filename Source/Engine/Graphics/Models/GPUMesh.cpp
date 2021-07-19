
#include "Vertex.h"
#include "GPUMesh.h"
#include "Engine/Graphics/GPUBuffer.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUBufferDescription.h"

using namespace DawnEngine;


bool GPUMesh::Init(MeshData& meshData)
{
	GPUBuffer* vertexBuffer = nullptr;
	GPUBuffer* indexBuffer = nullptr;
	
	// Create vertex buffer
	vertexBuffer = GPUDevice::Instance->CreateBuffer();
	auto vertexDesc = GPUBufferDescription::CreateVertexBufferDesc(sizeof(Vertex), meshData.Vertices.size(), meshData.Vertices.data());
	if (!vertexBuffer->Init(vertexDesc))
	{
		LOG_ERROR("[Mesh] Fail to create vertex buffer!");
		return false;
	}

	// Create index buffer
	indexBuffer = GPUDevice::Instance->CreateBuffer();
	auto indexDesc = GPUBufferDescription::CreateIndexBufferDesc(sizeof(uint32), meshData.Indices.size(), meshData.Indices.data());
	if (!indexBuffer->Init(indexDesc))
	{
		LOG_ERROR("[Mesh] Fail to create index buffer!");
		return false;
	}

	m_VertexBuffer = vertexBuffer;
	m_IndexBuffer = indexBuffer;
	m_IndicesCount = meshData.Indices.size();
	return true;
}

void GPUMesh::Release()
{
	if (m_VertexBuffer != nullptr)
	{
		m_VertexBuffer->ReleaseGPU();
		m_VertexBuffer = nullptr;
	}
	if (m_IndexBuffer != nullptr)
	{
		m_IndexBuffer->ReleaseGPU();
		m_IndexBuffer = nullptr;
	}
}