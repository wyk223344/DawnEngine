
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Graphics/Materials/CopyLinearMaterial.h"
#include "Engine/Graphics/Models/Mesh.h"
#include "Engine/Graphics/Models/GeometryGenerator.h"


using namespace DawnEngine;


GPUDevice* GPUDevice::Instance = nullptr;


struct GPUDevice::PrivateData
{
	CopyLinearMaterial* CopyLinearMaterial = nullptr;
	Mesh* QuadMesh = nullptr;
};



bool GPUDevice::Init()
{
	m_PrivateData = New<PrivateData>();
	return true;
}


bool GPUDevice::LoadContent()
{
	// init quad
	MeshData* quadMeshData = GeometryGenerator::CreateQuad(0.0f, 0.0f, 2.0f, 2.0f, 0.0f);
	Mesh* quadMesh = New<Mesh>();
	quadMesh->Init(*quadMeshData);
	m_PrivateData->QuadMesh = quadMesh;
	m_PrivateData->CopyLinearMaterial = New<CopyLinearMaterial>();
	m_PrivateData->CopyLinearMaterial->InitGPUResource();
	return true;
}


void GPUDevice::DrawBegin()
{
	m_IsRendering = true;
}

void GPUDevice::Draw()
{
	DrawBegin();

	auto context = GetMainContext();
	Window* window = Engine::MainWindow;
	auto swapChain = window->GetSwapChain();

	context->FrameBegin();

	Renderer::Render(context);

	context->FrameEnd();

	swapChain->Present();

	DrawEnd();
}

void GPUDevice::DrawEnd()
{
	m_IsRendering = false;
}

void GPUDevice::Dispose()
{

}

Mesh* GPUDevice::GetFullScreenQuadMesh()
{
	return m_PrivateData->QuadMesh;
}

CopyLinearMaterial* GPUDevice::GetCopyLinearMaterial()
{
	return m_PrivateData->CopyLinearMaterial;
}
