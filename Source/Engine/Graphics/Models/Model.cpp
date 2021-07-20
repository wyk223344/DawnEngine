
#include "Model.h"
#include "MeshData.h"
#include "Mesh.h"
#include "Engine/Graphics/Materials/MaterialBase.h"

using namespace DawnEngine;


bool Model::InitGPUResource()
{
	// init meshes
	for (int i = 0; i < m_MeshDatas.size(); i++)
	{
		Mesh* mesh = New<Mesh>();
		mesh->Init(*m_MeshDatas[i]);
		m_Meshes.push_back(mesh);
	}
	// init materials
	for (int i = 0; i < m_Materials.size(); i++)
	{
		m_Materials[i]->InitGPUResource();
	}
	return true;
}

void Model::Draw(GPUContext* context)
{
	for (int i = 0; i < m_Meshes.size(); i++)
	{
		m_Materials[i]->Draw(context);
		m_Meshes[i]->Draw(context);
	}
}

void Model::AddMeshAndMaterial(MeshData* meshData, MaterialBase* material)
{
	m_MeshDatas.push_back(meshData);
	m_Materials.push_back(material);
}