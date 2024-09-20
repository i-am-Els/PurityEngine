//
// Created by Eniola Olawale on 9/17/2024.
//


#pragma once

#include "isystems.h"
#include "tag_comp.h"
#include "id_comp.h"

namespace pnt::ecs{
    class ITagSystem : public ISystem<PTagComponent>{

    };

    class IIDSystem : public ISystem<PIDComponent>{

    };
}


