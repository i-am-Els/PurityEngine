//
// Created by Eniola Olawale on 1/9/2024.
//

#pragma once
#include "events.h"

namespace purity{

    class PURITY_API WindowCloseEvent : public Event{
    public:
        WindowCloseEvent() = default;

        EVENT_TYPE(E_EventType::WindowClose)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~WindowCloseEvent() override {
            PLog::echoMessage("Destroying Window Event.");
        }
    };

    class PURITY_API WindowResizeEvent : public Event{
    public:
        WindowResizeEvent(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}

        [[nodiscard]] inline uint32_t getWidth() const { return m_width; }
        [[nodiscard]] inline uint32_t getHeight() const { return m_height; }

        [[nodiscard]] std::string ToString() const override{
            std::stringstream ss;
            ss << "WindowResizeEvent: Window resized to {" << m_width << ", "<< m_height << "}";
            return ss.str();
        }
        EVENT_TYPE(E_EventType::WindowResize)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~WindowResizeEvent() override {
            PLog::echoMessage("Destroying Window Resized Event.");
        }

    private:
        uint32_t m_width, m_height;
    };

    class PURITY_API WindowMovedEvent : public Event{
    public:
        WindowMovedEvent(int x, int y) : xPos(x), yPos(y) {}

        [[nodiscard]] inline int getWidth() const { return xPos; }
        [[nodiscard]] inline int getHeight() const { return yPos; }

        [[nodiscard]] std::string ToString() const override{
            std::stringstream ss;
            ss << "WindowMovedEvent: Window moved to {" << xPos << ", "<< yPos << "}";
            return ss.str();
        }
        EVENT_TYPE(E_EventType::WindowMoved)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~WindowMovedEvent() override {
            PLog::echoMessage("Destroying Window Move Event.");
        }

    private:
        int xPos, yPos;
    };

    class PURITY_API WindowFocusEvent : public Event{
    public:
        explicit WindowFocusEvent(int focused) : m_focused(focused){}

        [[nodiscard]] inline int getFocused() const { return m_focused; }

        [[nodiscard]] std::string ToString() const override{
            std::stringstream ss;
            ss << "WindowFocusEvent: Focus is {" << m_focused << "}";
            return ss.str();
        }
        EVENT_TYPE(E_EventType::WindowFocused)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~WindowFocusEvent() override {
            PLog::echoMessage("Destroying Window Focus Event.");
        }
    private:
        int m_focused;
    };

    class PURITY_API WindowCursorEnterEvent : public Event{
    public:
        explicit WindowCursorEnterEvent(int entered) : m_entered(entered){}

        [[nodiscard]] inline int getEntered() const { return m_entered; }

        [[nodiscard]] std::string ToString() const override{
            std::stringstream ss;
            ss << "WindowCursorEnterEvent: Cursor Entered is {" << m_entered << "}";
            return ss.str();
        }
        EVENT_TYPE(E_EventType::WindowCursorEnter)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~WindowCursorEnterEvent() override {
            PLog::echoMessage("Destroying Window Cursor Enter Event.");
        }
    private:
        int m_entered;
    };

    class PURITY_API WindowLostFocusEvent : public Event{

    };


    // The three events below AppTickEvent, AppUpdateEvent and AppRenderEvent are quite intrinsic to an actual
    // application as "The Cherno" said, therefore, maybe the three events should just be hardcoded and be
    // non-modular events that are always present in an application.
    // It could be an option to implement it or not, but it's always there.
    // They might not have to take the route of first being received as an event and the dispatched to a function,
    // ... they are already called.
    class PURITY_API AppTickEvent : public Event{
    public:
        AppTickEvent() = default;

        EVENT_TYPE(E_EventType::AppTick)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~AppTickEvent() override {
            PLog::echoMessage("Destroying App Tick Event.");
        }
    };

    class PURITY_API AppUpdateEvent : public Event{
    public:
        AppUpdateEvent() = default;

        EVENT_TYPE(E_EventType::AppUpdate)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~AppUpdateEvent() override {
            PLog::echoMessage("Destroying App Update Event.");
        }
    };

    class PURITY_API AppRenderEvent : public Event{
    public:
        AppRenderEvent() = default;

        EVENT_TYPE(E_EventType::AppRender)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~AppRenderEvent() override {
            PLog::echoMessage("Destroying App Rendered Event.");
        }
    };
}



