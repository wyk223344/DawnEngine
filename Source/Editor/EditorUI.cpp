#include "EditorUI.h"
#include "Engine/Core/Include.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Engine/Base/ComponentBase.h"
#include "Engine/Engine/Components/TransformComponent.h"
#include "Engine/Gui/ImGuiHelper.h"
#include "ThirdParty/imgui/imgui.h"
#include "ThirdParty/imgui/imgui_internal.h"
#include "Engine/Engine/Globals.h"

using namespace DawnEngine;

void DrawVecControl(
    const std::string& label,
    Vector3& values,
    float              resetValue = 0.0f,
    float              columnWidth = 100.0f);

void DrawVecControl(
    const std::string& label,
    Quaternion& values,
    float              resetValue = 0.0f,
    float              columnWidth = 100.0f);


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

    DrawHierachyWindow();
    DrawInspectWindow();
    DrawGameWindow();
}


void EditorUI::DrawHierachyWindow()
{
	ImGui::Begin("Hierachy", nullptr, ImGuiWindowFlags_None);

    EntityBase* rootEntity = Engine::MainScene->GetRootEntity();

    for (EntityBase* child : rootEntity->GetChildren())
    {
        const std::string name = child->GetName();

        if (name.size() > 0)
        {
            std::size_t entityID = child->GetID();
            if (ImGui::Selectable(name.c_str(), m_SelectID == entityID))
            {
                m_SelectID = entityID;
            }
        }
    }

	ImGui::End();
}


void EditorUI::DrawInspectWindow()
{
	ImGui::Begin("Inspect", nullptr, ImGuiWindowFlags_None);

    EntityBase* selectEntity = nullptr;

    EntityBase* rootEntity = Engine::MainScene->GetRootEntity();

    for (EntityBase* child : rootEntity->GetChildren())
    {
        std::size_t entityID = child->GetID();
        if (entityID == m_SelectID)
        {
            selectEntity = child;
            break;
        }
    }

    if (selectEntity == nullptr)
    {
        ImGui::End();
        return;
    }

    const std::string entityName = selectEntity->GetName();

    ImGui::Text("Name");
    ImGui::SameLine();
    ImGui::Text(entityName.c_str());

    ImGui::Text("Transform");

    TransformComponent* transformComponent = selectEntity->GetComponent<TransformComponent>();

    DrawVecControl("Position", transformComponent->Transform.Translation);
    DrawVecControl("Rotation", transformComponent->Transform.Rotation);
    DrawVecControl("Scale", transformComponent->Transform.Scale);


	ImGui::End();
}


void EditorUI::DrawGameWindow()
{
    ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar);


    ImGui::End();
}


void DrawVecControl(const std::string& label, Vector3& values, float resetValue, float columnWidth)
{
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float  lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    if (ImGui::Button("X", buttonSize))
        values.X = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.X, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.45f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.55f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.45f, 0.2f, 1.0f });
    if (ImGui::Button("Y", buttonSize))
        values.Y = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.Y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    if (ImGui::Button("Z", buttonSize))
        values.Z = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.Z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);
    ImGui::PopID();
}

void DrawVecControl(const std::string& label, Quaternion& values, float resetValue, float columnWidth)
{
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float  lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    if (ImGui::Button("X", buttonSize))
        values.X = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.X, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.45f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.55f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.45f, 0.2f, 1.0f });
    if (ImGui::Button("Y", buttonSize))
        values.Y = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.Y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    if (ImGui::Button("Z", buttonSize))
        values.Z = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.Z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.25f, 0.5f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.6f, 0.35f, 0.6f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.5f, 0.25f, 0.5f, 1.0f });
    if (ImGui::Button("W", buttonSize))
        values.W = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##W", &values.W, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);
    ImGui::PopID();
}