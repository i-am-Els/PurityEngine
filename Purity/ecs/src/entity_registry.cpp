//
// Created by Eniola Olawale on 9/17/2024.
//

#include "entity_registry.h"
#include "entity_handle.h"
#include "handle_base.h"

namespace purity::ecs{
    PEntityHandle PEntityRegistry::Create(PUUID uuid) {
        auto entity = std::make_shared<PEntity>();
        m_entityMap.emplace(uuid, entity);
        ObjectRegistry::registerObject(entity);

        return PEntityHandle(m_entityMap[uuid]);
    }

    PEntityHandle PEntityRegistry::Create(PUUID uuid, const std::string &name) {
        const auto entity = std::make_shared<PEntity>();
        m_entityMap.emplace(uuid, std::make_unique<PEntity>(name));
        ObjectRegistry::registerObject(entity);

        return PEntityHandle(m_entityMap[uuid]);
    }

    void PEntityRegistry::Destroy(const commons::PUUID& uuid) {
        if (const auto it = m_entityMap.find(uuid); it != m_entityMap.end()) {
            m_entityMap.erase(it);
        }
    }

    PEntityHandle PEntityRegistry::GetEntity(commons::PUUID id) {
        for(const auto& [uuid, entity] : m_entityMap){
            if (entity->getUUID() == id){
                return PEntityHandle(entity);
            }
        }

        PEntityHandle p;
        p.m_handleId = (PUUID)0;
        return p;
    }

    std::vector<PEntityHandle> PEntityRegistry::GetEntitiesWithTag(const ETags tag, const std::unordered_set<PEntityHandle>& entitiesToIgnore){
        std::vector<PEntityHandle> entitiesWithTag = {};
        for(const auto& entity : m_entityMap | std::views::values){
            if(const auto tagComp = ecs::fetch_or_throw(entity->GetComponent<PTagComponent>())) {
                if (auto element = PEntityHandle(entity->weak_from_this()); tagComp->tag == tag && (!entitiesToIgnore.contains(element))) {
                    entitiesWithTag.push_back(element);
                }
            }
        }
        return entitiesWithTag;
    }

    PEntityRegistry::~PEntityRegistry() {
        if (!m_entityMap.empty())
            m_entityMap.clear();
        PLog::echoMessage("Destroying Entity Registry.");
    }

}

