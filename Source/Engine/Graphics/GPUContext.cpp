#include "GPUContext.h"
#include "GPUDevice.h"
#include "Engine/Graphics/Materials/CopyLinearMaterial.h"
#include "Engine/Graphics/Models/Mesh.h"


using namespace DawnEngine;

GPUContext::GPUContext(GPUDevice* device)
	: m_Device(device)
{
}


void GPUContext::FrameBegin()
{
}

void GPUContext::FrameEnd()
{
}

void GPUContext::DrawFullscreenTriangle()
{
	Mesh* quadMesh = m_Device->GetFullScreenQuadMesh();
	quadMesh->Draw(this);
}

void GPUContext::Draw(GPUTexture* srcRT)
{
	CopyLinearMaterial* material = m_Device->GetCopyLinearMaterial();
	material->SrcTexture = srcRT;
	material->Draw(this);
	DrawFullscreenTriangle();
}