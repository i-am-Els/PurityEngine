//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "core_macros.h"
#include "uuid.h"
#include "log.h"
using namespace commons;

namespace purity::fileIO{
    struct PURITY_API PHandleBase{
        commons::PUUID m_handleId;
        PHandleBase() {
            commons::PLog::echoMessage(LogLevel::Info, "Handle Base ID m_HandleID is %s", static_cast<std::string>(m_handleId).c_str());
        }

        PHandleBase(const PHandleBase& handle) = default;
//        PHandleBase(PHandleBase&& handle)  noexcept : m_handleId(handle.m_handleId) {
//
//        }


        virtual ~PHandleBase() {
            commons::PLog::echoMessage("Destroying Handle Base.");
        }

    private:
        static int s_count;
    };
}
