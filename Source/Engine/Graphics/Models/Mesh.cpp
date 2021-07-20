
#include "Vertex.h"
#include "Mesh.h"
#include "Engine/Graphics/GPUBuffer.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUBufferDescription.h"
#include "Engine/Graphics/GPUContext.h"

using namespace DawnEngine;


bool Mesh::Init(MeshData& meshData)
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

void Mesh::Draw(GPUContext* context)
{
	context->BindVB(GetVertexBuffer());
	context->BindIB(GetIndexBuffer());

	context->DrawIndexedInstanced(GetIndicesCount(), 1);
}

void Mesh::Release()
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