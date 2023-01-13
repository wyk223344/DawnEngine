#include "EditorUI.h"
#include "Engine/Gui/ImGuiHelper.h"
#include "ThirdParty/imgui/imgui.h"
#include "ThirdParty/imgui/imgui_internal.h"
#include "Engine/Engine/Globals.h"

using namespace DawnEngine;


void EditorUI::Draw()
{
    ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_DockSpace;
    ImGuiWindowFlags   window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
        ImGuiConfigFlags_NoMouseCursorChange | ImGuiWindowFlags_NoBringToFrontOnFocus;

    float width = Globals::Width;
    float height = Globals::Height;

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(main_viewport->WorkPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

    ImGui::SetNextWindowViewport(main_viewport->ID);

    ImGui::Begin("Editor menu", nullptr, window_flags);

    ImGuiID main_docking_id = ImGui::GetID("Main Docking");
    if (ImGui::DockBuilderGetNode(main_docking_id) == nullptr)
    {
        ImGui::DockBuilderRemoveNode(main_docking_id);

        ImGui::DockBuilderAddNode(main_docking_id, dock_flags);
        ImGui::DockBuilderSetNodePos(main_docking_id, ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y));
        ImGui::DockBuilderSetNodeSize(main_docking_id, ImVec2(Globals::Width, Globals::Height));

        ImGuiID center = main_docking_id;
        ImGuiID left;
        ImGuiID right = ImGui::DockBuilderSplitNode(center, ImGuiDir_Right, 0.25f, nullptr, &left);

        ImGuiID game_view;
        ImGuiID hierachy =  ImGui::DockBuilderSplitNode(left, ImGuiDir_Left, 0.30f, nullptr, &game_view);

        ImGui::DockBuilderDockWindow("Hierachy", hierachy);
        ImGui::DockBuilderDockWindow("Inspect", right);
        ImGui::DockBuilderDockWindow("Game", game_view);

        ImGui::DockBuilderFinish(main_docking_id);
    }

    ImGui::DockSpace(main_docking_id);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

	DrawHierachy();
	DrawInspect();
}


void EditorUI::DrawHierachy()
{
	//const float width = ImGui::GetIO().DisplaySize.x;
	//const float height = ImGui::GetIO().DisplaySize.y;
	//ImGui::SetNextWindowSize(ImVec2(200, height), ImGuiCond_Once);

	ImGui::Begin("Hierachy", nullptr, ImGuiWindowFlags_None);


	ImGui::End();

    ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar);


    ImGui::End();
}


void EditorUI::DrawInspect()
{
	//const float width = ImGui::GetIO().DisplaySize.x;
	//const float height = ImGui::GetIO().DisplaySize.y;
	//ImGui::SetNextWindowSize(ImVec2(200, height), ImGuiCond_Once);
	ImGui::Begin("Inspect", nullptr, ImGuiWindowFlags_None);

	ImGui::End();
}
