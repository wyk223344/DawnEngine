#include "LightPass.h"
#include "ShadowPass.h"
#include "RenderContext.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/Lights/DirectionalLight.h"

using namespace DawnEngine;


void LightPass::Init()
{
	ShadowPass::Instance()->Init();
}

void LightPass::Render(RenderContext* renderContext)
{
	if (renderContext->DirectionalLightList.size() == 0)
	{
		return;
	}
	auto directionalLight = renderContext->DirectionalLightList[0];
	ShadowPass::Instance()->RenderShadow(renderContext, directionalLight, renderContext->ShadowTexture);
}


void LightPass::Dispose()
{

}