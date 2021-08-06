#include "ShadowPass.h"
#include "RenderContext.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/Lights/LightBase.h"
#include "Engine/Graphics/Lights/DirectionalLight.h"
#include "Engine/Graphics/Lights/PointLight.h"
#include "Engine/Graphics/Lights/PointLight.h"
#include "Engine/Graphics/Materials/ShadowMaterial.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Graphics/Models/Mesh.h"

using namespace DawnEngine;


void ShadowPass::Init()
{
	m_ShadowMaterial = New<ShadowMaterial>();
	m_ShadowMaterial->InitGPUResource();
}

void ShadowPass::RenderShadow(RenderContext* renderContext, DirectionalLight* light, GPUTexture* renderTarget)
{
	GPUContext* context = GPUDevice::Instance->GetMainContext();

	renderContext->GlobalConstant.ViewProjMatrix = light->GetViewMatrix() * light->GetProjectionMatrix();
	context->UpdateCB(renderContext->GlobalConstantBuffer, &renderContext->GlobalConstant);

	context->SetViewportAndScissors(renderTarget->Width(), renderTarget->Height());
	context->ClearDepth(renderTarget);
	context->SetRenderTarget(nullptr, renderTarget);
	m_ShadowMaterial->Draw(context);
	for (auto drawCall : renderContext->DrawCallList)
	{
		renderContext->MeshConstant.WorldMatrix = drawCall.WorldMatrix;
		context->UpdateCB(renderContext->MeshConstantBuffer, &renderContext->MeshConstant);
		drawCall.Mesh->Draw(context);
	}
}

void ShadowPass::Dispose()
{

}