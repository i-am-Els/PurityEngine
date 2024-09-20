//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "pnt_core_pch.h"
#include "entity.h"

namespace pnt::ecs{
    class PEntityRegistry{
    public:
        PEntityRegistry() = default;
        ~PEntityRegistry();
        [[nodiscard]]PEntity* Create();
        [[nodiscard]]PEntity* Create(const std::string& name);
        void Destroy();
        void Destroy(PUUID uuid);

        PEntity* GetEntity(PUUID id);

        std::vector<PEntity*> GetEntitiesWithTag(ETags tag, const std::vector<PEntity*>& entitiesToIgnore = {});

    protected:
        std::vector<std::unique_ptr<PEntity>> entities;
    };
}