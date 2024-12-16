//
// Created by Eniola Olawale on 9/17/2024.
//


#pragma once

#include "isystems.h"
#include "tag_comp.h"
#include "id_comp.h"

namespace purity::ecs{
    class PURITY_API ITagSystem : public ISystem<PTagComponent>{

    };

    class PURITY_API IIDSystem : public ISystem<PIDComponent>{

    };
}


