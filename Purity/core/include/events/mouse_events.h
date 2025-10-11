//
// Created by Eniola Olawale on 1/9/2024.
//

#pragma once

#include "events.h"

namespace purity{

    class PURITY_API MouseButtonEvent : public Event {
    public:
        PURE_NODISCARD inline int getMouseButton() const { return m_button; }

        EVENT_CATEGORY(E_EventCategory::MouseBtnEvent | E_EventCategory::InputEvent)

        ~MouseButtonEvent() override {
            PLog::echoMessage("Destroying Mouse Event.");
        }

    protected:
        explicit MouseButtonEvent(const int button) : m_button(button) {}
        int m_button;
    };

    class PURITY_API MouseButtonPressedEvent final : public MouseButtonEvent{
    public:
        explicit MouseButtonPressedEvent(const int button) : MouseButtonEvent(button) {}

        PURE_NODISCARD std::string ToString() const override{
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button << " clicked";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::MouseButtonPressed)

        ~MouseButtonPressedEvent() override {
            PLog::echoMessage("Destroying Mouse Pressed Event.");
        }
    };

    class PURITY_API MouseButtonReleasedEvent final : public MouseButtonEvent{
    public:
        explicit MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button) {}

        PURE_NODISCARD std::string ToString() const override{
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button << " clicked";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::MouseButtonReleased)

        ~MouseButtonReleasedEvent() override {
            PLog::echoMessage("Destroying Mouse Released Event.");
        }
    };

    class PURITY_API MouseMovedEvent final : public Event{
    public:
        explicit MouseMovedEvent(const float x, const float y) : m_xPos(x), m_yPos(y) {}

        PURE_NODISCARD inline float getX() const { return m_xPos; }
        PURE_NODISCARD inline float getY() const { return m_yPos; }

        PURE_NODISCARD std::string ToString() const override{
            std::stringstream ss;
            ss << "MouseMovedEvent: Pointer at x{" << getX() << "}, y{" << getY() << "}";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::MouseMoved)
        EVENT_CATEGORY(E_EventCategory::MouseEvent | E_EventCategory::InputEvent)

        ~MouseMovedEvent() override {
            PLog::echoMessage("Destroying Mouse Moved Event.");
        }

    private:
        float m_xPos, m_yPos;
    };

    class PURITY_API MouseScrolledEvent final : public Event{
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

        PURE_NODISCARD inline float getXOffset() const { return m_xOffset; }
        PURE_NODISCARD inline float getYOffset() const { return m_yOffset; }

        PURE_NODISCARD std::string ToString() const override{
            std::stringstream ss;
            ss << "MouseScrolledEvent: Scroll offset at x{" << getXOffset() << "}, y{" << getYOffset() << "}";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::MouseScrolled)
        EVENT_CATEGORY(E_EventCategory::MouseEvent | E_EventCategory::InputEvent)

        ~MouseScrolledEvent() override {
            PLog::echoMessage("Destroying Mouse Scrolled Event.");
        }

    private:
        float m_xOffset, m_yOffset;
    };


}
