//
// Created by Eniola Olawale on 10/6/2024.
//

// EditorLayer.cpp
#include "editor_layer.h"
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>

#include "editors.h"
#include "imgui_opengl3_renderer.h"
#include "papplication.h"
#include "renderer_service_conc.h"
#include "window_purity.h"

namespace editor::gui
{

    EditorLayer::EditorLayer(const std::string &name) : PLayer(name){
    }

    EditorLayer::~EditorLayer()
    {
        PLog::echoMessage("Destroying Editor Layer");
    }

    void EditorLayer::update()
    {
        const auto window = PSystemFinder::GetWindow();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(static_cast<float>(window->getWidth()),
                               static_cast<float>(window->getHeight()));

        const auto time = static_cast<float>(glfwGetTime());
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderDockSpace();
        renderMainMenuBar();
        renderWindows();

        ImGui::Render();
    }

    void EditorLayer::attached()
    {
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow(); // Fixed typo

        auto* renderSystem = PSystemFinder::GetRendererService();

        if (!renderSystem) {
            std::cerr << "[Error] Could not cast PRenderComponent to POpenGLRenderSS!\n";
            throw exceptions::NullPointerError();
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        // Enable docking and viewports
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Docking configuration
        io.ConfigDockingWithShift = false;
        io.ConfigDockingAlwaysTabBar = true;
        io.ConfigDockingTransparentPayload = true;

        // Viewport configuration
        io.ConfigViewportsNoTaskBarIcon = true;
        io.ConfigViewportsNoAutoMerge = false;

        // Backend flags
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
        io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

        ImGui::StyleColorsDark();

        // Viewport style adjustment
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        PURITY_ASSERT_MSG(window != nullptr, "Window is a nullptr");
        ImGui_ImplGlfw_InitForOpenGL(window, false); // Diable callbacks
        ImGui_ImplOpenGL3_Init("#version 430 core");

        // Attach all windows
        for (auto& [name, window] : m_windows)
        {
            window->onAttach();
        }
    }

    void EditorLayer::detached()
    {
        // Detach all windows
        for (auto& [name, window] : m_windows)
        {
            window->onDetach();
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown(); // Fixed: Added missing shutdown
        ImGui::DestroyContext();
    }

    void EditorLayer::render()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void EditorLayer::renderDockSpace()
    {
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &m_dockspaceOpen, window_flags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            m_dockspaceID = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(m_dockspaceID, ImVec2(0.0f, 0.0f), dockspace_flags);

            // Setup initial layout on first run
            if (m_firstTime)
            {
                setupDockLayout();
                m_firstTime = false;
            }
        }

        ImGui::End();
    }

    void EditorLayer::renderMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N")) {}
                if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows"))
            {
                for (auto& [name, window] : m_windows)
                {
                    bool visible = window->isVisible();
                    if (ImGui::MenuItem(name.c_str(), nullptr, &visible))
                    {
                        window->setVisible(visible);
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Layout"))
            {
                if (ImGui::MenuItem("Save Layout"))
                {
                    saveLayoutToConfig();
                }
                if (ImGui::MenuItem("Load Layout"))
                {
                    loadLayoutFromConfig();
                    m_firstTime = true; // Trigger layout rebuild
                }
                if (ImGui::MenuItem("Reset to Default"))
                {
                    resetToDefaultLayout();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void EditorLayer::renderWindows()
    {
        for (auto& [name, window] : m_windows)
        {
            if (window->isVisible())
            {
                window->render();
            }
        }
    }

    void EditorLayer::setupDockLayout()
    {
        // Check if we should use a saved layout or default
        if (!m_dockingConfig.useDefaultLayout && !m_dockingConfig.areas.empty())
        {
            // Use configuration-based layout
            setupConfigurableLayout();
        }
        else
        {
            // Use default hardcoded layout as fallback
            setupDefaultLayout();
        }
    }

    void EditorLayer::setupDefaultLayout()
    {
        // Clear any existing layout
        ImGui::DockBuilderRemoveNode(m_dockspaceID);
        ImGui::DockBuilderAddNode(m_dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(m_dockspaceID, ImGui::GetMainViewport()->Size);

        // Split the dockspace
        ImGuiID dock_left, dock_right, dock_down;
        ImGui::DockBuilderSplitNode(m_dockspaceID, ImGuiDir_Left, 0.25f, &dock_left, &dock_right);
        ImGui::DockBuilderSplitNode(dock_right, ImGuiDir_Down, 0.3f, &dock_down, &dock_right);

        // Dock existing windows dynamically
        for (const auto& [name, window] : m_windows)
        {
            // Default placement logic based on window type/name
            if (name.find("Hierarchy") != std::string::npos ||
                name.find("Properties") != std::string::npos)
            {
                ImGui::DockBuilderDockWindow(name.c_str(), dock_left);
            }
            else if (name.find("Viewport") != std::string::npos ||
                     name.find("Scene") != std::string::npos)
            {
                ImGui::DockBuilderDockWindow(name.c_str(), dock_right);
            }
            else if (name.find("Console") != std::string::npos ||
                     name.find("Assets") != std::string::npos ||
                     name.find("Log") != std::string::npos)
            {
                ImGui::DockBuilderDockWindow(name.c_str(), dock_down);
            }
            else
            {
                // Unknown window type, dock to center
                ImGui::DockBuilderDockWindow(name.c_str(), dock_right);
            }
        }

        ImGui::DockBuilderFinish(m_dockspaceID);
    }

    void EditorLayer::setupConfigurableLayout()
    {
        // Clear any existing layout
        ImGui::DockBuilderRemoveNode(m_dockspaceID);
        ImGui::DockBuilderAddNode(m_dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(m_dockspaceID, ImGui::GetMainViewport()->Size);

        std::vector<ImGuiID> dockIds = { m_dockspaceID };

        // Create dock areas based on configuration
        for (const auto& area : m_dockingConfig.areas)
        {
            if (dockIds.empty()) break;

            ImGuiID current = dockIds.back();
            ImGuiID newDock, remainingDock;

            ImGui::DockBuilderSplitNode(current, area.direction, area.splitRatio,
                                       &newDock, &remainingDock);

            // Dock windows to this area
            for (const std::string& windowName : area.windows)
            {
                if (m_windows.find(windowName) != m_windows.end())
                {
                    ImGui::DockBuilderDockWindow(windowName.c_str(), newDock);
                }
            }

            // Replace current with remaining for next iteration
            dockIds.back() = remainingDock;
            if (area.direction != ImGuiDir_None)
            {
                dockIds.push_back(newDock);
            }
        }

        ImGui::DockBuilderFinish(m_dockspaceID);
    }

    void EditorLayer::loadLayoutFromConfig()
    {
        // Example: Load from JSON, INI, or your preferred config format
        // This is a simplified example - you'd implement your actual config loading

        m_dockingConfig.useDefaultLayout = false;
        m_dockingConfig.areas.clear();

        // Example configuration
        // DockingConfig::DockArea leftArea;
        // leftArea.name = "Left Panel";
        // leftArea.direction = ImGuiDir_Left;
        // leftArea.splitRatio = 0.25f;
        // leftArea.windows = {"Scene Hierarchy", "Properties"};
        //
        // DockingConfig::DockArea bottomArea;
        // bottomArea.name = "Bottom Panel";
        // bottomArea.direction = ImGuiDir_Down;
        // bottomArea.splitRatio = 0.3f;
        // bottomArea.windows = {"Console", "Assets"};
        //
        // m_dockingConfig.areas = {leftArea, bottomArea};

        // Alternative: Load from actual config file

        std::ifstream file("editor_layout.json");
        if (file.is_open())
        {
            // Parse JSON and populate m_dockingConfig
            // nlohmann::json config;
            // file >> config;
            // ... parse and set m_dockingConfig
        }
    }

    void EditorLayer::saveLayoutToConfig()
    {
        // Save current docking configuration
        // You could save ImGui's internal layout state or your custom config

        std::ofstream file("editor_layout.json");
        if (file.is_open())
        {
            nlohmann::json config;
            // Serialize m_dockingConfig to JSON
            // config["areas"] = ...;
            file << config.dump(4);
        }

    }

    void EditorLayer::resetToDefaultLayout()
    {
        m_dockingConfig.useDefaultLayout = true;
        m_firstTime = true; // Force layout reset on next frame
    }

    void EditorLayer::removeWindow(const std::string& name)
    {
        auto it = m_windows.find(name);
        if (it != m_windows.end())
        {
            it->second->onDetach();
            m_windows.erase(it);
        }
    }

    EditorWindow* EditorLayer::getWindow(const std::string& name)
    {
        auto it = m_windows.find(name);
        return (it != m_windows.end()) ? it->second.get() : nullptr;
    }

    void EditorLayer::setWindowVisible(const std::string& name, bool visible)
    {
        auto it = m_windows.find(name);
        if (it != m_windows.end())
        {
            it->second->setVisible(visible);
        }
    }

    void EditorLayer::setupEditor(EditorLayer* editor)
    {
        // Add windows to the editor
        editor->addWindow<definitions::SceneHierarchyWindow>("Scene Hierarchy");
        editor->addWindow<definitions::PropertiesWindow>("Properties");
        editor->addWindow<definitions::ViewportWindow>("Viewport");
        editor->addWindow<definitions::ConsoleWindow>("Console");
        editor->addWindow<definitions::AssetsWindow>("Assets");
    }

    void EditorLayer::eventFired(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressedEventCB));
        dispatcher.dispatch<MouseButtonReleasedEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnMouseButtonReleasedEventCB));
        dispatcher.dispatch<MouseMovedEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnMouseMovedEventCB));
        dispatcher.dispatch<MouseScrolledEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnMouseScrolledEventCB));
        dispatcher.dispatch<KeyPressedEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnKeyPressedEventCB));
        dispatcher.dispatch<KeyReleasedEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnKeyReleasedEventCB));
        // dispatcher.dispatch<WindowResizeEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnWindowResizedEventCB));
        dispatcher.dispatch<KeyTypedEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnKeyTypedEventCB));
        dispatcher.dispatch<WindowFocusEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnWindowFocusedEventCB));
        dispatcher.dispatch<WindowCursorEnterEvent>(PURITY_BIND_EVENT_FN(EditorLayer::OnWindowCursorEnterEventCB));
    }

    bool EditorLayer::OnMouseButtonPressedEventCB(const MouseButtonPressedEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Forward to ImGui using the backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const int button = e.getMouseButton(); // Your mouse button (0=left, 1=right, 2=middle)
        constexpr int action = GLFW_PRESS;
        constexpr int mods = 0; // You might need to get modifiers from your event

        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

        if (io.WantCaptureMouse) {
            return true; // Event consumed by ImGui
        }

        PLog::echoMessage("MousePressed");
        return false;
    }

    bool EditorLayer::OnMouseButtonReleasedEventCB(const MouseButtonReleasedEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Forward to ImGui using the backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const int button = e.getMouseButton();
        constexpr int action = GLFW_RELEASE;
        constexpr int mods = 0;

        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

        return io.WantCaptureMouse;
    }

    bool EditorLayer::OnMouseMovedEventCB(const MouseMovedEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Forward mouse position to ImGui using backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const double xpos = e.getX();
        const double ypos = e.getY();

        ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

        return io.WantCaptureMouse;
    }

    bool EditorLayer::OnMouseScrolledEventCB(const MouseScrolledEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Forward scroll to ImGui using backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const double xoffset = e.getXOffset();
        const double yoffset = e.getYOffset();

        ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

        return io.WantCaptureMouse;
    }

    bool EditorLayer::OnKeyPressedEventCB(const KeyPressedEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Use the modern ImGui GLFW backend function to forward key events
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const int key = e.getKeyCode();
        constexpr int action = GLFW_PRESS;
        constexpr int mods = 0; // You might need to get modifiers from your event if available

        // Forward to ImGui using the backend function
        ImGui_ImplGlfw_KeyCallback(window, key, 0, action, mods);

        return io.WantCaptureKeyboard;
    }

    bool EditorLayer::OnKeyReleasedEventCB(const KeyReleasedEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Use the modern ImGui GLFW backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const int key = e.getKeyCode();
        constexpr int action = GLFW_RELEASE;
        constexpr int mods = 0; // You might need to get modifiers from your event if available

        // Forward to ImGui using the backend function
        ImGui_ImplGlfw_KeyCallback(window, key, 0, action, mods);

        return io.WantCaptureKeyboard;
    }

    bool EditorLayer::OnKeyTypedEventCB(const KeyTypedEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Forward character input to ImGui using backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const unsigned int codepoint = e.getCharacter(); // Your character code

        ImGui_ImplGlfw_CharCallback(window, codepoint);

        return io.WantCaptureKeyboard;
    }

    bool EditorLayer::OnWindowFocusedEventCB(const WindowFocusEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Forward character input to ImGui using backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const int focused = e.getFocused();

        ImGui_ImplGlfw_WindowFocusCallback(window, focused);

        return io.WantCaptureMouse;
    }

    bool EditorLayer::OnWindowCursorEnterEventCB(const WindowCursorEnterEvent& e)
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Forward character input to ImGui using backend function
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow();
        const int entered = e.getEntered();

        ImGui_ImplGlfw_CursorEnterCallback(window, entered);

        return io.WantCaptureMouse;
    }
}