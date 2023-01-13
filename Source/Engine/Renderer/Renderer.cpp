

#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/ForwardPass.h"
#include "Engine/Renderer/LightPass.h"
#include "Engine/Renderer/RenderContext.h"
#include "Engine/Gui/ImGuiHelper.h"

using namespace DawnEngine;

#pragma region Renderer

#if GRAPHICS_API_DIRECTX12
namespace RendererImpl
{
    RenderContext* g_RenderContext;
}
#endif

void Renderer::Render(GPUContext* context)
{
    RenderContext* renderContext = RendererImpl::g_RenderContext;
    renderContext->BeforeDraw();

    context->BindCB((int32)GPUConstantBufferSlot::Global, renderContext->GlobalConstantBuffer);
    context->BindCB((int32)GPUConstantBufferSlot::Mesh, renderContext->MeshConstantBuffer);

    // LightPass::Instance()->Render(renderContext);

    context->BindSR(10, renderContext->ShadowTexture->View());

    ForwardPass::Instance()->Render(renderContext);

    Window* window = Engine::MainWindow;
    auto swapChain = window->GetSwapChain();
    auto backBuffer = swapChain->GetBackBuffer();

    context->SetViewportAndScissors(renderContext->Width, renderContext->Height);
    context->Clear(backBuffer->View(), Color::Gray);
    context->SetRenderTarget(backBuffer->View());
    context->Draw(renderContext->ForwardPassRT);

    ImGuiHelper::Instance()->BeforeDraw(renderContext);
    ImGuiHelper::Instance()->Draw(renderContext);
    ImGuiHelper::Instance()->AfterDraw(renderContext);
    //context->Draw(GPUDevice::Instance->GetColorTexture(Color::Blue));
    context->FlushState();
}

RenderContext* Renderer::GetRenderContext()
{
    return RendererImpl::g_RenderContext;
}

#pragma endregion


#pragma region RendererService

RendererService::RendererService() : EngineService(TEXT("Renderer"), 20)
{
}


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


