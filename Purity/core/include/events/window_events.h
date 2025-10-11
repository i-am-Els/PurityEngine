//
// Created by Eniola Olawale on 1/9/2024.
//

#pragma once
#include "events.h"

namespace purity{

    class PURITY_API WindowCloseEvent final : public Event{
    public:
        WindowCloseEvent() = default;

        EVENT_TYPE(E_EventType::WindowClose)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~WindowCloseEvent() override {
            PLog::echoMessage("Destroying Window Event.");
        }
    };

    class PURITY_API WindowResizeEvent final : public Event{
    public:
        WindowResizeEvent(const uint32_t width, const uint32_t height) : m_width(width), m_height(height) {}

        PURE_NODISCARD inline uint32_t getWidth() const { return m_width; }
        PURE_NODISCARD inline uint32_t getHeight() const { return m_height; }

        PURE_NODISCARD std::string ToString() const override{
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

    class PURITY_API WindowMovedEvent final : public Event{
    public:
        WindowMovedEvent(const int x, const int y) : xPos(x), yPos(y) {}

        PURE_NODISCARD inline int getWidth() const { return xPos; }
        PURE_NODISCARD inline int getHeight() const { return yPos; }

        PURE_NODISCARD std::string ToString() const override{
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

    class PURITY_API WindowFocusEvent final : public Event{
    public:
        explicit WindowFocusEvent(const int focused) : m_focused(focused){}

        PURE_NODISCARD inline int getFocused() const { return m_focused; }

        PURE_NODISCARD std::string ToString() const override{
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

    class PURITY_API WindowCursorEnterEvent final : public Event{
    public:
        explicit WindowCursorEnterEvent(const int entered) : m_entered(entered){}

        PURE_NODISCARD inline int getEntered() const { return m_entered; }

        PURE_NODISCARD std::string ToString() const override{
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
    class PURITY_API AppTickEvent final : public Event{
    public:
        AppTickEvent() = default;

        EVENT_TYPE(E_EventType::AppTick)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~AppTickEvent() override {
            PLog::echoMessage("Destroying App Tick Event.");
        }
    };

    class PURITY_API AppUpdateEvent final : public Event{
    public:
        AppUpdateEvent() = default;

        EVENT_TYPE(E_EventType::AppUpdate)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~AppUpdateEvent() override {
            PLog::echoMessage("Destroying App Update Event.");
        }
    };

    class PURITY_API AppRenderEvent final : public Event{
    public:
        AppRenderEvent() = default;

        EVENT_TYPE(E_EventType::AppRender)

        EVENT_CATEGORY(E_EventCategory::ApplicationEvent)

        ~AppRenderEvent() override {
            PLog::echoMessage("Destroying App Rendered Event.");
        }
    };
}



