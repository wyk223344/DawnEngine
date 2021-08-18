
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Graphics/Materials/CopyLinearMaterial.h"
#include "Engine/Graphics/Models/Mesh.h"
#include "Engine/Graphics/Models/GeometryGenerator.h"
#include "Engine/Graphics/Textures/GPUTexture.h"

#include <vector>
#include <map>

using namespace DawnEngine;


GPUDevice* GPUDevice::Instance = nullptr;


struct GPUDevice::PrivateData
{
	CopyLinearMaterial* CopyLinearMaterial = nullptr;
	Mesh* QuadMesh = nullptr;
	std::map<uint32, GPUTexture*> ColorTextureDict;
};



bool GPUDevice::Init()
{
	m_PrivateData = New<PrivateData>();
	return true;
}


bool GPUDevice::LoadContent()
{
	GPUContext* context = GetMainContext();
	// init quad
	MeshData* quadMeshData = GeometryGenerator::CreateQuad(0.0f, 0.0f, 2.0f, 2.0f, 0.0f);
	Mesh* quadMesh = New<Mesh>();
	quadMesh->Init(*quadMeshData);
	m_PrivateData->QuadMesh = quadMesh;
	m_PrivateData->CopyLinearMaterial = New<CopyLinearMaterial>();
	m_PrivateData->CopyLinearMaterial->InitGPUResource();
	// init color texture
	std::vector<Color> colorList = { Color::White, Color::Black, Color::Gray, Color::Red, Color::Green, Color::Blue };
	auto colorTextureDesc = GPUTextureDescription::New2D(1, 1, PixelFormat::R8G8B8A8_UNorm);
	uint32 arrayColorData[1] = { 0 };
	for each (Color color in colorList)
	{
		arrayColorData[0] = color.ToRGBA();
		GPUTexture* colorTexture = CreateTexture();
		colorTexture->Init(colorTextureDesc);
		context->UpdateTexture(colorTexture, 0, 0, arrayColorData, 4, 4);
		m_PrivateData->ColorTextureDict[color.GetHashCode()] = colorTexture;
	}
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

GPUTexture* GPUDevice::GetColorTexture(Color color)
{
	return m_PrivateData->ColorTextureDict[color.GetHashCode()];
}
