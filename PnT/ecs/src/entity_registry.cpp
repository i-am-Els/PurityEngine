//
// Created by Eniola Olawale on 9/17/2024.
//

#include "entity_registry.h"

namespace pnt::ecs{
    PEntity *PEntityRegistry::Create(PUUID uuid) {
        m_entityMap.emplace(uuid, std::make_unique<PEntity>());

        return m_entityMap[uuid].get();
    }

    PEntity *PEntityRegistry::Create(PUUID uuid, const std::string &name) {
        m_entityMap.emplace(uuid, std::make_unique<PEntity>(name));

        return m_entityMap[uuid].get();
    }

    void PEntityRegistry::Destroy() {

    }

    void PEntityRegistry::Destroy(pnt::PUUID uuid) {

    }

    PEntity *PEntityRegistry::GetEntity(pnt::PUUID id) {
        for(const auto& [uuid, entity] : m_entityMap){
            if (entity->m_instanceID == id){
                return entity.get();
            }
        }
        return nullptr;
    }

    std::vector<PEntity*> PEntityRegistry::GetEntitiesWithTag(ETags tag, const std::vector<PEntity*>& entitiesToIgnore){
        std::vector<PEntity*> entitiesWithTag = {};
        for(auto& [uuid, entity] : m_entityMap){
            if(auto tagComp = entity->GetComponent<PTagComponent>()){
                if (tagComp->tag == tag && (std::find(entitiesToIgnore.begin(), entitiesToIgnore.end(), entity.get()) == entitiesToIgnore.end())){
                    entitiesWithTag.push_back(entity.get());
                }
            }
        }
        return entitiesWithTag;
    }

    PEntityRegistry::~PEntityRegistry() {
        m_entityMap.clear();
        PLog::echoMessage("Destroying Entity Registry.");
    }

}

