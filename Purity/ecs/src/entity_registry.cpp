//
// Created by Eniola Olawale on 9/17/2024.
//

#include "entity_registry.h"
#include "handle_base.h"

namespace purity::ecs{
    PEntityHandle PEntityRegistry::Create(PUUID uuid) {
        m_entityMap.emplace(uuid, std::make_unique<PEntity>());

        return PEntityHandle(m_entityMap[uuid].get());
    }

    PEntityHandle PEntityRegistry::Create(PUUID uuid, const std::string &name) {
        m_entityMap.emplace(uuid, std::make_unique<PEntity>(name));

        return PEntityHandle(m_entityMap[uuid].get());
    }

    void PEntityRegistry::Destroy() {

    }

    void PEntityRegistry::Destroy(purity::PUUID uuid) {

    }

    PEntityHandle PEntityRegistry::GetEntity(purity::PUUID id) {
        for(const auto& [uuid, entity] : m_entityMap){
            if (entity->m_instanceID == id){
                return PEntityHandle(entity.get());
            }
        }

        PEntityHandle p;
        p.m_handleId = (PUUID)0;
        return p;
    }

    std::vector<PEntityHandle> PEntityRegistry::GetEntitiesWithTag(ETags tag, const std::unordered_set<PEntityHandle>& entitiesToIgnore){
        std::vector<PEntityHandle> entitiesWithTag = {};
        for(auto& [uuid, entity] : m_entityMap){
            if(auto tagComp = entity->GetComponent<PTagComponent>()) {
                auto element = PEntityHandle(entity.get());
                if (tagComp->tag == tag && (entitiesToIgnore.find(element) == entitiesToIgnore.end())) {

                    entitiesWithTag.emplace_back(entity.get());
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

