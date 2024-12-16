//
// Created by Eniola Olawale on 1/9/2024.
//

#pragma once
#include "events.h"

namespace purity{

    class PURITY_API KeyEvent : public Event {
    public:
        [[nodiscard]] inline int getKeyCode() const { return m_keyCode; }

        EVENT_CATEGORY(E_EventCategory::KeyBoardEvent | E_EventCategory::InputEvent)

        ~KeyEvent() override {
            PLog::echoMessage("Destroying Key Event.");
        }

    protected:
        explicit KeyEvent(int keyCode) : m_keyCode(keyCode) {}

        int m_keyCode;
    };

    class PURITY_API KeyPressedEvent : public KeyEvent{
    public:
        explicit KeyPressedEvent(int keyCode, int repeatCount=0) : KeyEvent(keyCode), m_repeat_count(repeatCount) {}

        [[nodiscard]] inline int getRepeatCount() const { return m_repeat_count; }

        [[nodiscard]] std::string ToString() const override{
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeat_count << " repeats)";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::KeyPressed)

        ~KeyPressedEvent() override {
            PLog::echoMessage("Destroying Key Pressed Event.");
        }

    private:
        int m_repeat_count;
    };

    class PURITY_API KeyReleasedEvent : public KeyEvent{
    public:
        explicit KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        [[nodiscard]] std::string ToString() const override{
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode << " released";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::KeyReleased)

        ~KeyReleasedEvent() override {
            PLog::echoMessage("Destroying Key Released Event.");
        }
    };

}



