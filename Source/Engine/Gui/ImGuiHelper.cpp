
#include "ImGuiHelper.h"
#include "ImGuiExtensions.h"
#include "ThirdParty/imgui/imgui.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Platform/Window.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Renderer/RenderContext.h"
#include "Engine/Gui/UIBase.h"

#ifdef PLATFORM_WINDOWS
#include "ThirdParty/imgui/imgui_impl_win32.h"
#endif 

#ifdef GRAPHICS_API_DIRECTX12
#include "ThirdParty/imgui/imgui_impl_dx12.h"
#include "Engine/GraphicsDevice/DX12/GPUDeviceDX12.h"
#include "Engine/GraphicsDevice/DX12/GPUContextDX12.h"
#endif 




using namespace DawnEngine;


namespace ImGuiHelperImpl
{
	CopyLinearMaterial* TestMaterial;
	float TempFloat;
	bool TempBool;
}


ImGuiHelper::ImGuiHelper()
	: m_RenderMaterial(nullptr)
	, m_FontTexture(nullptr)
{
}


bool ImGuiHelper::Init()
{
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigDockingAlwaysTabBar = true;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(1.0, 0);
	style.FramePadding = ImVec2(14.0, 2.0f);
	style.ChildBorderSize = 0.0f;
	style.FrameRounding = 5.0f;
	style.FrameBorderSize = 1.5f;

#ifdef PLATFORM_WINDOWS
	ImGui_ImplWin32_Init(Engine::MainWindow->GetNativePtr());
#endif 

#ifdef GRAPHICS_API_DIRECTX12
	DX12::GPUDeviceDX12* deviceDX12 = static_cast<DX12::GPUDeviceDX12*>(device);
	ImGui_ImplDX12_Init(deviceDX12->GetDevice(), 2, DXGI_FORMAT_R8G8B8A8_UNORM,
		deviceDX12->ImGui_Heap_Srv.Get(),
		deviceDX12->ImGui_Heap_Srv.Get()->GetCPUDescriptorHandleForHeapStart(),
		deviceDX12->ImGui_Heap_Srv.Get()->GetGPUDescriptorHandleForHeapStart()
	);
#endif 

	return true;
}

void ImGuiHelper::SetDisplaySize(int width, int height, float scaleX, float scaleY)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(width, height);
	io.DisplayFramebufferScale.x = scaleX;
	io.DisplayFramebufferScale.y = scaleY;
}

void ImGuiHelper::Draw(RenderContext* renderContext)
{

	for each (UIBase * uiBase in m_UIVector)
	{
		uiBase->Draw();
	}

	//ImGuiIO& io = ImGui::GetIO(); (void)io;

	//// Disable rounding and draw a fixed-height ImGui window that looks like a sidebar.
	//ImGui::GetStyle().WindowRounding = 0;
	//ImGui::SetNextWindowPos(ImVec2(0, 0));

	//const float width = ImGui::GetIO().DisplaySize.x;
	//const float height = ImGui::GetIO().DisplaySize.y;
	//ImGui::SetNextWindowSize(ImVec2(200, height), ImGuiCond_Once);
	//ImGui::SetNextWindowSizeConstraints(ImVec2(20, height), ImVec2(width, height));

	//ImGui::Begin("DawnEngine", nullptr, ImGuiWindowFlags_NoTitleBar);

	//auto& lightSettings = renderContext->Settings.Light;
	//if (ImGui::CollapsingHeader("Light"))
	//{
	//	ImGui::Indent();
	//	if (ImGui::CollapsingHeader("Sunlight"))
	//	{
	//		ImGui::SliderFloat("Sun intensity", &lightSettings.SunLightIntensity, 50000.0, 150000.0f);
	//		
	//		//ImGuiExt::DirectionWidget("Sun direction", light.sunlightDirection.v);
	//	}
	//	ImGui::Unindent();
	//}

	//static int counter = 0;

	//ImGui::Begin("Hello, world!");
	//ImGui::Text("This is some useful text.");
	//ImGui::Checkbox("Demo Window", &ImGuiHelperImpl::TempBool);      // Edit bools storing our window open/close state

	//ImGui::SliderFloat("float", &ImGuiHelperImpl::TempFloat, 0.1f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//	counter++;
	//ImGui::SameLine();
	//ImGui::Text("counter = %d", counter);
	//ImGui::Text("io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y);
	//ImGui::Text("io.DisplayFramebufferScale: %.2f,%.2f", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	//ImGui::End();
}


void ImGuiHelper::BeforeDraw(RenderContext* renderContext)
{
#ifdef GRAPHICS_API_DIRECTX12
	ImGui_ImplDX12_NewFrame();
#endif
#ifdef PLATFORM_WINDOWS
	ImGui_ImplWin32_NewFrame();
#endif 
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::NewFrame();
}


void ImGuiHelper::AfterDraw(RenderContext* renderContext)
{
	ImGui::Render();

#ifdef GRAPHICS_API_DIRECTX12
	GPUDevice* device = GPUDevice::Instance;
	DX12::GPUDeviceDX12* deviceDX12 = static_cast<DX12::GPUDeviceDX12*>(device);
	DX12::GPUContextDX12* contextDX12 = static_cast<DX12::GPUContextDX12*>(device->GetMainContext());
	contextDX12->GetCommandList()->SetDescriptorHeaps(1, deviceDX12->ImGui_Heap_Srv.GetAddressOf());
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), contextDX12->GetCommandList());
#endif
}


void ImGuiHelper::AddUI(UIBase* ui)
{
	m_UIVector.push_back(ui);
}