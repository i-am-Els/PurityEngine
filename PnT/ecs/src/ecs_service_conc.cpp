//
// Created by emman on 8/8/2024.
//

#include "ecs_service_conc.h"

namespace pnt{
    std::map<std::type_index, std::unique_ptr<ISystemBase>> PECSService::system_map;
}