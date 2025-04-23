//
// Created by Eniola Olawale on 06/04/2025.
//

#include "imgui_layer.h"

#include <imgui_impl_glfw.h>
// #include <GLFW/glfw3.h>
// #ifdef _WIN32
// #undef APIENTRY
// #ifndef GLFW_EXPOSE_NATIVE_WIN32
// #define GLFW_EXPOSE_NATIVE_WIN32
// #endif
// #include <GLFW/glfw3native.h>   // for glfwGetWin32Window()
// #endif

#include "imgui.h"
#include "imgui_opengl3_renderer.h"
#include "window_purity.h"

namespace editor::gui {
// -------------------------------------------- SAFE ZONE -----------------------------------------------

    void ImGuiLayer::update()
    {
        auto window = PSystemFinder::GetWindow();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(static_cast<float>(window->getWidth()), static_cast<float>(window->getHeight()));

        auto time = static_cast<float>(glfwGetTime());
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        static bool showDemoWindow = true;
        ImGui::ShowDemoWindow(&showDemoWindow);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::attached()
    {
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        // Setup Context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // io.KeyMaps -- TODO - Add this // io.AddKeyEvent(Im)

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		  // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigViewportsNoAutoMerge = false;
        io.ConfigViewportsNoTaskBarIcon = true;

        PURITY_ASSERT_MSG(window != nullptr, "Window is a nullptr");
        ImGui_ImplGlfw_InitForOpenGL(window, false);
        ImGui_ImplOpenGL3_Init("#version 430 core"); // TODO - read this sorts of values from an ini
    }

    void ImGuiLayer::detached()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::eventFired(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEventCB));
        dispatcher.dispatch<MouseButtonReleasedEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEventCB));
        dispatcher.dispatch<MouseMovedEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEventCB));
        dispatcher.dispatch<MouseScrolledEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEventCB));
        dispatcher.dispatch<KeyPressedEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEventCB));
        dispatcher.dispatch<KeyReleasedEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEventCB));
        dispatcher.dispatch<WindowResizeEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEventCB));
        // dispatcher.dispatch<KeyTypedEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEventCB));

    }

    bool ImGuiLayer::OnMouseButtonPressedEventCB(const MouseButtonPressedEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEventCB(const MouseButtonReleasedEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnMouseMovedEventCB(const MouseMovedEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEventCB(const MouseScrolledEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEventCB(const KeyPressedEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEventCB(const KeyReleasedEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnWindowResizedEventCB(const WindowResizeEvent& e)
    {
        return false;
    }

    ImGuiLayer::ImGuiLayer(const std::string &name) : PLayer(name){
    }

    ImGuiLayer::~ImGuiLayer()
    {
        PLog::echoMessage("Destroying ImGui Layer");
    }

    // -------------------------------- Anything that brakes happened here ---------------------------------------------


} // purity