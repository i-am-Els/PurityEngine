//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "../../core/include/log.h"
#include "uuid.h"

namespace pnt::fileIO{
    struct PNT_API PHandleBase{
        pnt::PUUID m_handleId;
        PHandleBase() {
            PLog::echoValue(m_handleId);
        }
    private:
        static int s_count;
    };
}
