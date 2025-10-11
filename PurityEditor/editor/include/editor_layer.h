// EditorLayer.h
#pragma once
#include <imgui.h>

#include <utility>
#include "purity_core_pch.h"


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

    class EditorWindow
    {
    public:
        explicit EditorWindow(std::string  name, bool* open = nullptr, const DockArea preferredArea = DockArea::None)
            : m_name(std::move(name)), m_open(open), m_visible(true), m_preferredDockArea(preferredArea) {}
        virtual ~EditorWindow() = default;

        virtual void render() = 0;
        virtual void onAttach() {}
        virtual void onDetach() {}

        // Docking preferences
        PURE_NODISCARD DockArea getPreferredDockArea() const { return m_preferredDockArea; }
        void setPreferredDockArea(const DockArea area) { m_preferredDockArea = area; }
        PURE_NODISCARD virtual float getPreferredSplitRatio() const { return 0.25f; } // Override in derived classes

        PURE_NODISCARD const std::string& getName() const { return m_name; }
        PURE_NODISCARD bool isVisible() const { return m_visible; }
        void setVisible(const bool visible) { m_visible = visible; }

    protected:
        std::string m_name;
        bool* m_open;
        bool m_visible;
        DockArea m_preferredDockArea;
    };

    class EditorLayer final : public purity::PLayer
    {
    public:
        void update() override;
        void attached() override;
        void detached() override;
        void render() override;
        void eventFired(purity::Event& event) override;

        // Window management
        template<typename T, typename... Args>
        T* addWindow(const std::string& name, Args&&... args);

        void removeWindow(const std::string& name);
        EditorWindow* getWindow(const std::string& name);
        void setWindowVisible(const std::string& name, bool visible);

        static void setupEditor(EditorLayer* editor);
        bool isOverlay() override { return true; }

    private:
        void renderMainMenuBar();
        void renderDockSpace();
        void renderWindows();
        void setupDockLayout();
        void setupDefaultLayout();
        void setupConfigurableLayout();
        void loadLayoutFromConfig();
        void saveLayoutToConfig();
        void resetToDefaultLayout();

        // Layout configuration
        struct DockingConfig
        {
            struct DockArea
            {
                std::string name;
                float splitRatio;
                ImGuiDir direction;
                std::vector<std::string> windows;
            };

            std::vector<DockArea> areas;
            bool useDefaultLayout = true;
        } m_dockingConfig;

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