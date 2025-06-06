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
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
        // Debug current mouse state
        PLog::echoMessage(LogLevel::Info, "Mouse Pos: %s, %s", std::to_string(io.MousePos.x).c_str(), std::to_string(io.MousePos.y).c_str());
        PLog::echoMessage(LogLevel::Info, "Mouse Down: %s", std::to_string(io.MouseDown[0]).c_str());
        static bool showDemoWindow = true;
        ImGui::ShowDemoWindow(&showDemoWindow);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

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
        // io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		  // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigViewportsNoAutoMerge = false;
        io.ConfigViewportsNoTaskBarIcon = true;

        // IMPORTANT: Configure mouse and keyboard capture
        io.WantCaptureMouse = false;      // Start with false, will be set per-frame
        io.WantCaptureKeyboard = false;   // Start with false, will be set per-frame
        io.WantTextInput = false;         // For text input


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
        // dispatcher.dispatch<WindowResizeEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEventCB));
        dispatcher.dispatch<KeyTypedEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEventCB));
        dispatcher.dispatch<WindowFocusEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnWindowFocusedEventCB));
        dispatcher.dispatch<WindowCursorEnterEvent>(PURITY_BIND_EVENT_FN(ImGuiLayer::OnWindowCursorEnterEventCB));
    }

    bool ImGuiLayer::OnMouseButtonPressedEventCB(const MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Forward to ImGui using the backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        int button = e.getMouseButton(); // Your mouse button (0=left, 1=right, 2=middle)
        int action = GLFW_PRESS;
        int mods = 0; // You might need to get modifiers from your event

        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

        if (io.WantCaptureMouse) {
            return true; // Event consumed by ImGui
        }

        PLog::echoMessage("MousePressed");
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEventCB(const MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Forward to ImGui using the backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        int button = e.getMouseButton();
        int action = GLFW_RELEASE;
        int mods = 0;

        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

        return io.WantCaptureMouse;
    }

    bool ImGuiLayer::OnMouseMovedEventCB(const MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Forward mouse position to ImGui using backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        double xpos = e.getX();
        double ypos = e.getY();

        ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

        return io.WantCaptureMouse;
    }

    bool ImGuiLayer::OnMouseScrolledEventCB(const MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Forward scroll to ImGui using backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        double xoffset = e.getXOffset();
        double yoffset = e.getYOffset();

        ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

        return io.WantCaptureMouse;
    }

    bool ImGuiLayer::OnKeyPressedEventCB(const KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Use the modern ImGui GLFW backend function to forward key events
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        int key = e.getKeyCode();
        int action = GLFW_PRESS;
        int mods = 0; // You might need to get modifiers from your event if available

        // Forward to ImGui using the backend function
        ImGui_ImplGlfw_KeyCallback(window, key, 0, action, mods);

        return io.WantCaptureKeyboard;
    }

    bool ImGuiLayer::OnKeyReleasedEventCB(const KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Use the modern ImGui GLFW backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        int key = e.getKeyCode();
        int action = GLFW_RELEASE;
        int mods = 0; // You might need to get modifiers from your event if available

        // Forward to ImGui using the backend function
        ImGui_ImplGlfw_KeyCallback(window, key, 0, action, mods);

        return io.WantCaptureKeyboard;
    }

    bool ImGuiLayer::OnKeyTypedEventCB(const KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Forward character input to ImGui using backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        unsigned int codepoint = e.getCharacter(); // Your character code

        ImGui_ImplGlfw_CharCallback(window, codepoint);

        return io.WantCaptureKeyboard;
    }

    bool ImGuiLayer::OnWindowFocusedEventCB(const WindowFocusEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Forward character input to ImGui using backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        int focused = e.getFocused();

        ImGui_ImplGlfw_WindowFocusCallback(window, focused);

        return io.WantCaptureMouse;
    }

    bool ImGuiLayer::OnWindowCursorEnterEventCB(const WindowCursorEnterEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Forward character input to ImGui using backend function
        auto window = PSystemFinder::GetWindow()->getGlfWwindow();
        int entered = e.getEntered();

        ImGui_ImplGlfw_CursorEnterCallback(window, entered);

        return io.WantCaptureMouse;
    }

    // bool ImGuiLayer::OnWindowResizedEventCB(const WindowResizeEvent& e)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //
    //     // Forward character input to ImGui using backend function
    //     auto window = PSystemFinder::GetWindow()->getGlfWwindow();
    //
    //
    //     ImGui_ImplGlfw_
    //
    //     return io.WantCaptureMouse;
    // }

    ImGuiLayer::ImGuiLayer(const std::string &name) : PLayer(name){
    }

    ImGuiLayer::~ImGuiLayer()
    {
        PLog::echoMessage("Destroying ImGui Layer");
    }

    // -------------------------------- Anything that brakes happened here ---------------------------------------------


} // purity