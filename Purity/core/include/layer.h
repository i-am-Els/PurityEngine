//
// Created by Eniola Olawale on 3/10/2024.
//

#pragma once

#include <utility>

#include "purity_core_pch.h"


namespace purity {
    constexpr size_t ARRAY_SIZE = 32;

    class PApplication;

    class Event;

    class PURITY_API PLayer {
    public:
        inline void enable() { m_enabled = true; }
        inline void disable() { m_enabled = false; }
        [[nodiscard]] [[maybe_unused]] inline bool isEnabled() const { return m_enabled; }

        explicit operator unsigned int() const { return m_id; }
        explicit operator std::string() const { return m_name; }
        PLayer(): m_id(PUUID()), m_name(static_cast<std::string>("Layer" + m_id)) {}
        [[nodiscard]] inline PUUID getID() const{ return static_cast<PUUID>(m_id); }

        virtual ~PLayer() { PLog::echoMessage("Destroying Layer.");};
        explicit PLayer(std::string name) : m_id(PUUID()), m_name(std::move(name)), m_enabled(true) {}

        virtual void update() {}
        virtual void attached() {}
        virtual void detached() {}
        virtual void eventFired(Event & event) {}
    protected:
        unsigned int m_id{};
        std::string m_name;
        bool m_enabled{};
    };
    // ========================================= END OF LAYERS =======================================
} // purity


