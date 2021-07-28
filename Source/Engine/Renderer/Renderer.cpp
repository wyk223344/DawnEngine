
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/Enums.h"
#include "Renderer.h"
#include "ForwardPass.h"
#include "RenderContext.h"

using namespace DawnEngine;

#pragma region Renderer

namespace RendererImpl
{
    RenderContext* g_RenderContext;
}


void Renderer::Render(GPUContext* context)
{
    RenderContext* renderContext = RendererImpl::g_RenderContext;
    renderContext->BeforeDraw();

    context->UpdateCB(renderContext->GlobalConstantBuffer, &renderContext->GlobalConstant);
    context->BindCB((int32)GPUConstantBufferSlot::Global, renderContext->GlobalConstantBuffer);
    context->BindCB((int32)GPUConstantBufferSlot::Mesh, renderContext->MeshConstantBuffer);
    ForwardPass::Instance()->Render(renderContext);

    Engine::MainScene->DrawSkybox(context);

    context->FlushState();
}

#pragma endregion


#pragma region RendererService

class RendererService : public EngineService
{
public:

    RendererService()
        : EngineService(TEXT("Renderer"), 20)
    {
    }

    bool Init() override;
    void Dispose() override;
};

RendererService RendererServiceInstance;

bool RendererService::Init()
{
    RenderContext* renderContext = New<RenderContext>();
    renderContext->Init(Globals::Width, Globals::Height);
    RendererImpl::g_RenderContext = renderContext;
    ForwardPass::Instance()->Init();
    return true;
}

void RendererService::Dispose()
{
    ForwardPass::Instance()->Dispose();
}

#pragma endregion

