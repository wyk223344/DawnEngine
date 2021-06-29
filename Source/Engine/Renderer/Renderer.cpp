
#include "Renderer.h"
#include "ForwardPass.h"
#include "Engine/Graphics/GPUContext.h"

using namespace DawnEngine;


void Renderer::Render(GPUContext* context)
{
	ForwardPass::Instance()->Render(context);
}