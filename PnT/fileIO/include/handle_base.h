//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "core_macros.h"

namespace pnt::fileIO{
    struct PNT_API PHandleBase{
        pnt::PUUID m_handleId;
        PHandleBase() {
            pnt::PLog::echoValue(m_handleId);
        }

        PHandleBase(const PHandleBase& handle) = default;
//        PHandleBase(PHandleBase&& handle)  noexcept : m_handleId(handle.m_handleId) {
//
//        }


        virtual ~PHandleBase() {
            pnt::PLog::echoMessage("Destroying Handle Base.");
        }

    private:
        static int s_count;
    };
}
