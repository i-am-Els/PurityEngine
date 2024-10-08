//
// Created by Eniola Olawale on 10/8/2024.
//

#pragma once

#include "pnt_core_pch.h"
#include "entity.h"


namespace pnt::ecs {
    class PNT_API PEntityHandle final : public fileIO::PHandleBase {
    public:
        PEntityHandle() : PHandleBase(), m_data(nullptr) {}

        // Constructor to initialize with an existing PEntity pointer
        explicit PEntityHandle(PEntity* entity) : PHandleBase(), m_data(entity) {}

        // Destructor
        ~PEntityHandle() override {
            // Prevent dangling pointer usage after destruction
            m_data = nullptr;
            PLog::echoMessage("Destroying PEntityHandle.");
        }

        // Optionally, provide access to the PEntity
//        PEntity* getEntity() const { return m_data; }
//        void setEntity(PEntity* entity) { m_data = entity; }

    private:
        PEntity* m_data; // Raw pointer; the handle does not own this data

        // Other entity operations...
    };
}


