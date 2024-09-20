//
// Created by Eniola Olawale on 9/17/2024.
//

#include "entity_registry.h"

namespace pnt::ecs{
    PEntity *PEntityRegistry::Create() {
        entities.emplace_back(std::make_unique<PEntity>());

        return entities.back().get();
    }

    PEntity *PEntityRegistry::Create(const std::string &name) {
        entities.emplace_back(std::make_unique<PEntity>(name));

        return entities.back().get();
    }

    void PEntityRegistry::Destroy() {

    }

    void PEntityRegistry::Destroy(pnt::PUUID uuid) {

    }

    PEntity *PEntityRegistry::GetEntity(pnt::PUUID id) {
        for(const auto& entity : entities ){
            if (entity->m_instanceID == id){
                return entity.get();
            }
        }
        return nullptr;
    }

    std::vector<PEntity*> PEntityRegistry::GetEntitiesWithTag(ETags tag, const std::vector<PEntity*>& entitiesToIgnore){
        std::vector<PEntity*> entitiesWithTag = {};
        for(auto& entity : entities){
            if(auto tagComp = entity->GetComponent<PTagComponent>()){
                if (tagComp->tag == tag && (std::find(entitiesToIgnore.begin(), entitiesToIgnore.end(), entity.get()) == entitiesToIgnore.end())){
                    entitiesWithTag.push_back(entity.get());
                }
            }
        }
        return entitiesWithTag;
    }

    PEntityRegistry::~PEntityRegistry() {
        entities.clear();
    }

}

