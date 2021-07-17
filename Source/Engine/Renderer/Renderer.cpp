
#include "Engine/Engine/EngineService.h"
#include "Renderer.h"
#include "ForwardPass.h"
#include "Engine/Graphics/GPUContext.h"

using namespace DawnEngine;

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
    // ForwardPass::Instance()->Init();
    return true;
}

void RendererService::Dispose()
{
    ForwardPass::Instance()->Dispose();
}

#pragma endregion



void Renderer::Render(GPUContext* context)
{
	ForwardPass::Instance()->Render(context);
}