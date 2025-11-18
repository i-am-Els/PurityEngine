//
// Created by Eniola Olawale on 07/06/2025.
//

#pragma once
#include "editor_layer.h"

namespace editor::gui::definitions
{
    // Example Window Implementations
    class SceneHierarchyWindow final : public EditorWindow
    {
    public:
        explicit SceneHierarchyWindow(const std::string& name) : EditorWindow(name, nullptr, DockArea::Left) {}

        PURE_NODISCARD float getPreferredSplitRatio() const override { return 0.25f; }

        void render() override
        {
            if (ImGui::Begin(m_name.c_str(), &m_visible))
            {
                if (ImGui::TreeNode("Scene"))
                {
                    if (ImGui::TreeNode("GameObject 1"))
                    {
                        ImGui::Text("Transform");
                        ImGui::Text("Mesh Renderer");
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNode("GameObject 2"))
                    {
                        ImGui::Text("Transform");
                        ImGui::Text("Light");
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::End();
        }
    };

    class PropertiesWindow final : public EditorWindow
    {
    public:
        explicit PropertiesWindow(const std::string& name) : EditorWindow(name, nullptr, DockArea::Left) {}

        void render() override
        {
            if (ImGui::Begin(m_name.c_str(), &m_visible))
            {
                ImGui::Text("GameObject Properties");
                ImGui::Separator();

                if (ImGui::CollapsingHeader("Transform"))
                {
                    static float pos[3] = {0.0f, 0.0f, 0.0f};
                    static float rot[3] = {0.0f, 0.0f, 0.0f};
                    static float scale[3] = {1.0f, 1.0f, 1.0f};

                    ImGui::DragFloat3("Position", pos, 0.1f);
                    ImGui::DragFloat3("Rotation", rot, 0.1f);
                    ImGui::DragFloat3("Scale", scale, 0.1f);
                }

                if (ImGui::CollapsingHeader("Mesh Renderer"))
                {
                    ImGui::Text("Material: Default");
                    static auto color = ImVec4(1, 1, 1, 1); // persistent variable
                    ImGui::ColorEdit3("Color", reinterpret_cast<float*>(&color));
                }
            }
            ImGui::End();
        }
    };

    class ViewportWindow final : public EditorWindow
    {
    public:
        explicit ViewportWindow(const std::string& name) : EditorWindow(name, nullptr, DockArea::Center) {}

        void render() override
        {
            if (ImGui::Begin(m_name.c_str(), &m_visible))
            {
                ImVec2 viewportSize = ImGui::GetContentRegionAvail();

                // Render your 3D scene here
                ImGui::Text("3D Viewport");
                ImGui::Text("Size: %.1f x %.1f", viewportSize.x, viewportSize.y);

                // Example: Render a colored rectangle as placeholder
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
                ImVec2 canvas_size = ImGui::GetContentRegionAvail();

                draw_list->AddRectFilled(canvas_pos,
                    ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
                    IM_COL32(50, 50, 50, 255));

                draw_list->AddText(ImVec2(canvas_pos.x + 10, canvas_pos.y + 10),
                    IM_COL32(255, 255, 255, 255), "3D Scene Rendering Here");
            }
            ImGui::End();
        }
    };

    class ConsoleWindow final : public EditorWindow
    {
    public:
        explicit ConsoleWindow(const std::string& name) : EditorWindow(name, nullptr, DockArea::Bottom) {}

        PURE_NODISCARD float getPreferredSplitRatio() const override { return 0.3f; }

        void render() override
        {
            if (ImGui::Begin(m_name.c_str(), &m_visible))
            {
                static std::vector<std::string> logs = {
                    "[INFO] Editor initialized",
                    "[INFO] Scene loaded successfully",
                    "[WARNING] Texture not found: missing.png",
                    "[ERROR] Shader compilation failed"
                };

                for (const auto& log : logs)
                {
                    ImGui::Text("%s", log.c_str());
                }

                ImGui::Separator();
                static char inputBuf[256] = "";
                if (ImGui::InputText("Command", inputBuf, sizeof(inputBuf),
                    ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    logs.push_back(std::string("> ") + inputBuf);
                    inputBuf[0] = '\0';
                }
            }
            ImGui::End();
        }
    };

    class AssetsWindow final : public EditorWindow
    {
    public:
        explicit AssetsWindow(const std::string& name) : EditorWindow(name, nullptr, DockArea::Bottom) {}

        void render() override
        {
            if (ImGui::Begin(m_name.c_str(), &m_visible))
            {
                if (ImGui::TreeNode("Textures"))
                {
                    ImGui::Selectable("grass.png");
                    ImGui::Selectable("stone.png");
                    ImGui::Selectable("wood.png");
                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Models"))
                {
                    ImGui::Selectable("cube.obj");
                    ImGui::Selectable("sphere.obj");
                    ImGui::Selectable("character.fbx");
                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("Materials"))
                {
                    ImGui::Selectable("Default.mat");
                    ImGui::Selectable("Metallic.mat");
                    ImGui::TreePop();
                }
            }
            ImGui::End();
        }
    };
}
