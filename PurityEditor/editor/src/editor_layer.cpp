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
#include "window_purity.h"

namespace editor::gui
{
    enum class DockArea
    {
        Left,
        Right,
        Bottom,
        Top,
        Center,
        None  // Let ImGui decide or user manual docking
    };

    EditorLayer::EditorLayer(const std::string &name) : PLayer(name){
    }

    EditorLayer::~EditorLayer()
    {
        PLog::echoMessage("Destroying Editor Layer");
    }

    void EditorLayer::renderImGuiEditorData()
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
        // int display_w, display_h;
        // Get the real-time size of the window
        // const auto glfwWindow = window->getGLFWwindow();
        // const auto clear_color = PSystemFinder::GetApplication()->m_projectEditorInfo.clearColor;
        // glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
        // Use that size to set the viewport
        // glViewport(0, 0, display_w, display_h);
        // glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // renderImGuiEditorData(io);
    }

    void EditorLayer::attached()
    {
        const auto window = PSystemFinder::GetWindow()->getGLFWwindow(); // Fixed typo

        auto* renderSystem = dynamic_cast<POpenGLRenderSS*>(PSystemFinder::GetECSService()->getSystem<PRenderComponent>());

        if (!renderSystem) {
            std::cerr << "[Error] Could not cast PRenderComponent to POpenGLRenderSS!\n";
        } else {
            renderSystem->setEditorRenderCallback(std::function<void()>(EditorLayer::renderImGuiEditorData));
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
        // Clear any existing layout
        ImGui::DockBuilderRemoveNode(m_dockspaceID);
        ImGui::DockBuilderAddNode(m_dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(m_dockspaceID, ImGui::GetMainViewport()->Size);

        // Split the dockspace
        ImGuiID dock_left, dock_right, dock_down;
        ImGui::DockBuilderSplitNode(m_dockspaceID, ImGuiDir_Left, 0.25f, &dock_left, &dock_right);
        ImGui::DockBuilderSplitNode(dock_right, ImGuiDir_Down, 0.3f, &dock_down, &dock_right);

        // Dock windows to specific areas (these will be created by example windows)
        ImGui::DockBuilderDockWindow("Scene Hierarchy", dock_left);
        ImGui::DockBuilderDockWindow("Properties", dock_left);
        ImGui::DockBuilderDockWindow("Viewport", dock_right);
        ImGui::DockBuilderDockWindow("Console", dock_down);
        ImGui::DockBuilderDockWindow("Assets", dock_down);

        ImGui::DockBuilderFinish(m_dockspaceID);
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