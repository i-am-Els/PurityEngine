//
// Created by Eniola Olawale on 9/17/2024.
//


#pragma once

#include "isystems.h"
#include "tag_comp.h"
#include "id_comp.h"

namespace pnt::ecs{
    class PNT_API ITagSystem : public ISystem<PTagComponent>{

    };

    class PNT_API IIDSystem : public ISystem<PIDComponent>{

    };
}


