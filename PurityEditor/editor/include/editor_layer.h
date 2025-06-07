// EditorLayer.h
#pragma once
#include <imgui.h>

#include <utility>
#include "purity_core_pch.h"
#include "papplication.h"
namespace editor::gui
{
    class EditorWindow
    {
    public:
        explicit EditorWindow(std::string  name, bool* open = nullptr)
            : m_name(std::move(name)), m_open(open), m_visible(true) {}
        virtual ~EditorWindow() = default;

        virtual void render() = 0;
        virtual void onAttach() {}
        virtual void onDetach() {}

        [[nodiscard]] const std::string& getName() const { return m_name; }
        [[nodiscard]] bool isVisible() const { return m_visible; }
        void setVisible(const bool visible) { m_visible = visible; }

    protected:
        std::string m_name;
        bool* m_open;
        bool m_visible;
    };

    class EditorLayer final : public purity::PLayer
    {
    public:
        void update() override;
        void attached() override;
        void detached() override;
        void eventFired(purity::Event& event) override;

        // Window management
        template<typename T, typename... Args>
        T* addWindow(const std::string& name, Args&&... args);

        void removeWindow(const std::string& name);
        EditorWindow* getWindow(const std::string& name);
        void setWindowVisible(const std::string& name, bool visible);

        static void setupEditor(EditorLayer* editor);
    private:
        void renderMainMenuBar();
        void renderDockSpace();
        void renderWindows();
        void setupDockLayout();

        std::unordered_map<std::string, std::unique_ptr<EditorWindow>> m_windows;
        bool m_dockspaceOpen = true;
        bool m_firstTime = true;
        ImGuiID m_dockspaceID;
        float m_time = 0.0f;

        friend class PLayerService;
        friend class editor::PEditorApplication;
    private:
        bool OnMouseButtonPressedEventCB(const MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEventCB(const MouseButtonReleasedEvent& e);
        bool OnMouseMovedEventCB(const MouseMovedEvent& e);
        bool OnMouseScrolledEventCB(const MouseScrolledEvent& e);
        bool OnKeyPressedEventCB(const KeyPressedEvent& e);
        bool OnKeyReleasedEventCB(const KeyReleasedEvent& e);
        bool OnKeyTypedEventCB(const KeyTypedEvent& e);
        // bool OnWindowResizedEventCB(const WindowResizeEvent& e);
        bool OnWindowFocusedEventCB(const WindowFocusEvent& e);
        bool OnWindowCursorEnterEventCB(const WindowCursorEnterEvent& e);
    protected:
        explicit EditorLayer(const std::string& name);
    public:
        EditorLayer() = delete;
        ~EditorLayer() override;
        static void renderImGuiEditorData();
    };

    template<typename T, typename... Args>
    T* EditorLayer::addWindow(const std::string& name, Args&&... args)
    {
        auto window = std::make_unique<T>(name, std::forward<Args>(args)...);
        T* ptr = window.get();
        m_windows[name] = std::move(window);
        return ptr;
    }
}