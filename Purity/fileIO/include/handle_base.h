//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "core_macros.h"
#include "uuid.h"
#include "log.h"

namespace purity::fileIO{
    struct PURITY_API PHandleBase{
        commons::PUUID m_handleId;
        PHandleBase() {
            purity::PLog::echoValue(m_handleId);
        }

        PHandleBase(const PHandleBase& handle) = default;
//        PHandleBase(PHandleBase&& handle)  noexcept : m_handleId(handle.m_handleId) {
//
//        }


        virtual ~PHandleBase() {
            purity::PLog::echoMessage("Destroying Handle Base.");
        }

    private:
        static int s_count;
    };
}
