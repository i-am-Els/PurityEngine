//
// Created by Eniola Olawale on 9/17/2024.
//

#include "entity_registry.h"
#include "entity_handle.h"
#include "handle_base.h"
#include "ecs_conc.h"
#include "scene.h"

namespace purity::ecs{
    PEntityIndex PEntityRegistry::createIndex() {
        if (!m_freeIndices.empty())
        {
            auto index = m_freeIndices.front();
            m_freeIndices.pop();
            return index;
        }

        return { s_indexCounter++, 0 };
    }

    void PEntityRegistry::removeIndex(PEntityIndex index) {
        ++index.generation;
        m_freeIndices.push(index);
    }


    PEntityHandle PEntityRegistry::Create(PUUID uuid) {
        auto [it, inserted] = m_entityMap.emplace(
            uuid,
            std::make_shared<PEntity>(uuid)
        );
        if (!inserted) {
            PLog::echoMessage(LogLevel::Warning, "PUUID %s already exists in the registry... returning its entity handle", PUUID::to_string(uuid).c_str());
            return GetEntity(uuid);
        }
        it->second->setIndex(createIndex());

        return PEntityHandle(it->second, this);
    }

    PEntityHandle PEntityRegistry::Create(PUUID uuid, const std::string &name) {
        auto [it, inserted] = m_entityMap.emplace(
            uuid,
            std::make_shared<PEntity>(uuid)
        );
        if (!inserted) {
            PLog::echoMessage(LogLevel::Warning, "PUUID %s already exists in the registry... returning its entity handle", PUUID::to_string(uuid).c_str());
            return GetEntity(uuid);
        }
        it->second->setIndex(createIndex());
        it->second->m_name = name;

        return PEntityHandle(it->second, this);
    }

    void PEntityRegistry::Destroy(const commons::PUUID& uuid)
    {
        auto it = m_entityMap.find(uuid);

        if (it == m_entityMap.end())
            return;

        removeIndex(it->second->m_index);
        m_entityMap.erase(it);
    }

    PEntityHandle PEntityRegistry::GetEntity(commons::PUUID id) {
        if (const auto it = m_entityMap.find(id); it != m_entityMap.end())
        {
            return PEntityHandle(it->second, this);
        }

        PEntityHandle p(this);
        p.m_handleId = (PUUID)0;
        return p;
    }

    std::vector<PEntityHandle> PEntityRegistry::GetEntitiesWithTag(const ETags tag, const std::unordered_set<PEntityHandle>& entitiesToIgnore) {
        std::vector<PEntityHandle> entitiesWithTag = {};
        
        if (!m_ownerScene) return entitiesWithTag;   // no owning scene — nothing to query against

        for (const auto& entity : m_entityMap | std::views::values) {
            if (const auto tagComp = fetch_or_throw(GetECSService().GetComponent<PTagComponent>(entity->m_index))) {
                if (tagComp->tag != tag) continue;
                if (!entitiesToIgnore.empty() && entitiesToIgnore.contains(PEntityHandle(entity->weak_from_this(), this))) continue;
                entitiesWithTag.push_back(PEntityHandle(entity->weak_from_this(), this));
            }
        }
        return entitiesWithTag;
    }

    PURE_NODISCARD PECSService& PEntityRegistry::GetECSService() const {
        if (!m_ownerScene) {
            PLOG_ERROR("GetECSService called with no owning scene.");
            throw std::runtime_error("PEntityRegistry::GetECSService: no owning scene.");
        }
        return m_ownerScene->m_ecsService;
    }

    PEntityRegistry::~PEntityRegistry() {
        if (!m_entityMap.empty())
            m_entityMap.clear();
        PLog::echoMessage("Destroying Entity Registry.");
    }

}

