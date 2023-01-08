

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






#include "Engine/Platform/Define.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Graphics/Graphics.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/Textures/GPUTexture.h"

#if GRAPHICS_API_DIRECTX12
#include "Engine/GraphicsDevice/DX12/GPUDeviceDX12.h"
#endif 


using namespace DawnEngine;


#if GRAPHICS_API_DIRECTX12
//extern GPUDevice* CreateGPUDeviceDX12();
#endif 

#pragma region GraphicsService

class GraphicsService : public EngineService
{
public:
    GraphicsService() : EngineService(TEXT("Graphics"), -40)
    {
        LOG_INFO("GraphicsService");
    }

    bool Init() override;
    void Draw() override;
    void BeforeExit() override;
    void Dispose() override;
};


GraphicsService GraphicsServiceInstance;


bool GraphicsService::Init()
{
    GPUDevice* device = nullptr;

#if GRAPHICS_API_DIRECTX12
    //device = CreateGPUDeviceDX12();
    device = DX12::GPUDeviceDX12::Create();
#endif

    if (device == nullptr)
    {
        return false;
    }

    GPUDevice::Instance = device;

    if (!device->LoadContent())
    {
        return false;
    }

    return true;
}

void GraphicsService::Draw()
{
    if (GPUDevice::Instance != nullptr)
    {
        GPUDevice::Instance->Draw();
    }
}

void GraphicsService::BeforeExit()
{

}


void GraphicsService::Dispose()
{

}

#pragma endregion


void Graphics::Render()
{

}