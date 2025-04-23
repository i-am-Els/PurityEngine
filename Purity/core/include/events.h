//
// Created by Eniola Olawale on 1/9/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "core_macros.h"
#include "layer.h"

namespace purity{

    /// Isle Engine - This is a revolutionary game engine

    enum class E_EventType{
        None=0,
        AppUpdate, AppRender, AppTick,
        WindowClose, WindowMoved, WindowResize, WindowFocused, WindowLostFocus,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum E_EventCategory{
        None                =0,
        ApplicationEvent    =BIT(0),
        InputEvent          =BIT(1),
        MouseEvent          =BIT(2),
        MouseBtnEvent       =BIT(3),
        KeyBoardEvent       =BIT(4)
    };

//    These macros below are definitions of function overrides that are used in the event classes implementations
//    as shorthands instead of typing out everything manually
//    Note: you are to make use of scoped enums i.e "E_EventType::keyPressed" instead of just "KeyPressed".
//    Look at-{return #type;}, the # before the "type" is a stringifier operator
//    that converts a token/parameter into a string literal */
#define EVENT_TYPE(type) static E_EventType s_GetStaticType() { return type; } \
                                virtual E_EventType getEventType() const override { return s_GetStaticType(); } \
                                virtual const char* getName() const override { return #type; }  \

#define EVENT_CATEGORY(category) virtual int getCategories() const override { return category; }



    class PURITY_API Event {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;

        [[nodiscard]] virtual E_EventType getEventType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;
        [[nodiscard]] virtual int getCategories() const = 0;
        [[nodiscard]] virtual std::string ToString() const { return getName(); }

        [[nodiscard]] inline bool isInCategory(E_EventCategory category) const
        {
            return ( getCategories() & category );
        }
        [[nodiscard]] inline bool getHandled() const { return m_handled; }

    protected:
        bool m_handled = false;
    };


    class PURITY_API EventDispatcher{
        /** @brief Type required for event callbacks to be used in the event dispatcher
         * @return bool
         * @note Expects a bool return from the callback denoting whether it handled the event and
         * it should stop being progragating down to other layers **/
        template<class T>
        using pEventFunc = std::function<bool(const T&)>;
    public:
        explicit EventDispatcher(Event& event) : m_Event (event) { }

        template<class T>
        bool dispatch(pEventFunc<T> callbackFunc)
        {

            // Ensuring Type Safety
            static_assert(std::is_base_of_v<Event, T>, "T must be derived from Event");
            if (m_Event.getEventType() == T::s_GetStaticType()){ // Here lies the reason for having pEventFunc as a template definition
                // Because Event the base class does not declare the s_GetStaticType() method.

                // The callback returns a bool denoting whether it handled the event and it should stop being progragating down to other layers or dispatchers.
                m_Event.m_handled = callbackFunc(*static_cast<T*>(&m_Event));
                return true;
            }
            return false;
        }

        ~EventDispatcher() {
            PLog::echoMessage("Destroying Event Dispatcher.");
        }


    private:
        Event& m_Event;
    };



    inline std::ostream& operator<<(std::ostream& stream, const Event& e){
        stream << e.ToString() << std::endl;
        return stream;
    }

    class PURITY_API EventQueue {

    };
}



