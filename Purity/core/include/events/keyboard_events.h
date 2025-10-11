//
// Created by Eniola Olawale on 1/9/2024.
//

#pragma once
#include "events.h"

namespace purity{

    class PURITY_API KeyEvent : public Event {
    public:
        PURE_NODISCARD inline int getKeyCode() const { return m_keyCode; }

        EVENT_CATEGORY(E_EventCategory::KeyBoardEvent | E_EventCategory::InputEvent)

        ~KeyEvent() override {
            PLog::echoMessage("Destroying Key Event.");
        }


    protected:
        explicit KeyEvent(const int keyCode) : m_keyCode(keyCode) {}

        int m_keyCode;
    };

    class PURITY_API KeyPressedEvent final : public KeyEvent{
    public:
        explicit KeyPressedEvent(const int keyCode, const int repeatCount=0) : KeyEvent(keyCode), m_repeat_count(repeatCount) {}

        PURE_NODISCARD inline int getRepeatCount() const { return m_repeat_count; }

        PURE_NODISCARD std::string ToString() const override{
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

    class PURITY_API KeyReleasedEvent final : public KeyEvent{
    public:
        explicit KeyReleasedEvent(const int keyCode) : KeyEvent(keyCode) {}

        PURE_NODISCARD std::string ToString() const override{
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode << " released";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::KeyReleased)

        ~KeyReleasedEvent() override {
            PLog::echoMessage("Destroying Key Released Event.");
        }
    };

    class PURITY_API KeyTypedEvent final : public Event  // Note: NOT inheriting from KeyEvent
{
    private:
        unsigned int m_Character;

    public:
        explicit KeyTypedEvent(const unsigned int character) : m_Character(character) {}

        PURE_NODISCARD inline unsigned int getCharacter() const { return m_Character; }

        PURE_NODISCARD std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: '" << static_cast<char>(m_Character)
               << "' (codepoint: " << m_Character << ")";
            return ss.str();
        }

        EVENT_TYPE(E_EventType::KeyTyped)
        EVENT_CATEGORY(E_EventCategory::KeyBoardEvent | E_EventCategory::InputEvent)
    };

}



