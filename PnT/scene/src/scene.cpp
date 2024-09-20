//
// Created by Eniola Olawale on 9/17/2024.
//

#include "scene.h"
#include "tag_comp.h"
#include "id_comp.h"

PEntity* pnt::PScene::CreateEntity(const std::string &name) {
    return CreateEntityWithUUID(PUUID(), name);
}

PEntity* pnt::PScene::CreateEntityWithUUID(pnt::PUUID uuid, const std::string& name) {
    // Add entity to Entity Registry
    auto entity = m_registry.Create(name);
    // Add ID Component
    auto id = entity->AddComponent<PIDComponent>();
    // Set ID
    id->setID(uuid);
    // Add Transform Component,
    entity->m_transform = entity->AddComponent<PTransformComponent>();
    // Add Tag Component
    auto tag = entity->AddComponent<PTagComponent>();
    // Add Entity to Entity Map
    m_entityMap[uuid] = entity;
    PLog::echoMessage(LogLevel::Info, "%s %s %s", "Entity", "in Scene with ID:", static_cast<std::string>(id->m_entityInstanceID).c_str());
    return entity;
}

void pnt::PScene::DestroyEntity(PEntity entity) {

}

void pnt::PScene::DestroyEntityWithUUID(pnt::PUUID uuid) {

}

pnt::PScene::PScene(const std::unordered_map<PUUID, PEntity *>& entityMap, const PEntityRegistry& registry) {

}
