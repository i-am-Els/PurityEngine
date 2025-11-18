//
// Created by Eniola Olawale on 06/04/2025.
//

#pragma once

#include "keyboard_events.h"
#include "layer.h"
#include "mouse_events.h"
#include "window_events.h"

using namespace purity;

namespace editor{
    class PEditorApplication;
    namespace gui {
    // ===============================================================================================
    // ======================================= START OF ImGuiLayer =====================================


        class ImGuiLayer final : public purity::PLayer{
        public:
            void update() override;
            void attached() override;
            void detached() override;
            void eventFired(purity::Event& event) override;

        private:
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
            explicit ImGuiLayer(const std::string& name);
        public:
            ImGuiLayer() = delete;
            ~ImGuiLayer() override;

        };
        // ======================================== END OF ImGuiLayer ========================================
        // =================================================================================================
        // purity
    }
}
