

//#include "Engine/Platform/Define.h"
//#include "Engine/Engine/EngineService.h"
//#include "Engine/Graphics/Graphics.h"
//#include "Engine/Graphics/GPUDevice.h"
//#include "Engine/Engine/Engine.h"
//#include "Engine/Engine/EngineService.h"
//#include "Engine/Engine/Globals.h"
//#include "Engine/Engine/Scene.h"
//#include "Engine/Graphics/GPUContext.h"
//#include "Engine/Graphics/GPUDevice.h"
//#include "Engine/Graphics/Enums.h"
//#include "Engine/Graphics/Textures/GPUTexture.h"
//
//#if GRAPHICS_API_DIRECTX12
//#include "Engine/GraphicsDevice/DX12/GPUDeviceDX12.h"
//#endif 
//
//
//using namespace DawnEngine;
//
//
//#if GRAPHICS_API_DIRECTX12
////extern GPUDevice* CreateGPUDeviceDX12();
//#endif 
//
//#pragma region GraphicsService
//
//class GraphicsService : public EngineService
//{
//public:
//    GraphicsService() : EngineService(TEXT("Graphics"), -40)
//    {
//        LOG_INFO("GraphicsService");
//    }
//
//    bool Init() override;
//    void Draw() override;
//    void BeforeExit() override;
//    void Dispose() override;
//};
//
//
//GraphicsService GraphicsServiceInstance;
//
//
//bool GraphicsService::Init()
//{
//    GPUDevice* device = nullptr;
//
//#if GRAPHICS_API_DIRECTX12
//    //device = CreateGPUDeviceDX12();
//    device = DX12::GPUDeviceDX12::Create();
//#endif
//
//    if (device == nullptr)
//    {
//        return false;
//    }
//
//    GPUDevice::Instance = device;
//
//    if (!device->LoadContent())
//    {
//        return false;
//    }
//
//    return true;
//}
//
//void GraphicsService::Draw()
//{
//    if (GPUDevice::Instance != nullptr)
//    {
//        GPUDevice::Instance->Draw();
//    }
//}
//
//void GraphicsService::BeforeExit()
//{
//
//}
//
//
//void GraphicsService::Dispose()
//{
//
//}
//
//#pragma endregion
//
//
//void Graphics::Render()
//{
//
//}


