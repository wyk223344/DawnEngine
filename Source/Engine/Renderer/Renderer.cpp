
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Renderer.h"
#include "ForwardPass.h"
#include "LightPass.h"
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

    context->BindCB((int32)GPUConstantBufferSlot::Global, renderContext->GlobalConstantBuffer);
    context->BindCB((int32)GPUConstantBufferSlot::Mesh, renderContext->MeshConstantBuffer);

    LightPass::Instance()->Render(renderContext);

    context->BindSR(10, renderContext->ShadowTexture->View());

    ForwardPass::Instance()->Render(renderContext);

    Window* window = Engine::MainWindow;
    auto swapChain = window->GetSwapChain();
    auto backBuffer = swapChain->GetBackBuffer();

    context->SetViewportAndScissors(renderContext->Width, renderContext->Height);
    context->Clear(backBuffer->View(), Color::Gray);
    context->SetRenderTarget(backBuffer->View());
    context->Draw(renderContext->ForwardPassRT);
    //context->Draw(GPUDevice::Instance->GetColorTexture(Color::Blue));
    context->FlushState();
}

RenderContext* Renderer::GetRenderContext()
{
    return RendererImpl::g_RenderContext;
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
    LightPass::Instance()->Init();
    return true;
}

void RendererService::Dispose()
{
    ForwardPass::Instance()->Dispose();
}

#pragma endregion

