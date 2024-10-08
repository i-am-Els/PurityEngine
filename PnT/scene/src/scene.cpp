//
// Created by Eniola Olawale on 9/17/2024.
//

#include "scene.h"
#include "tag_comp.h"
#include "id_comp.h"


namespace pnt::scene{
    PEntity* PScene::CreateEntity(const std::string &name) {
        return CreateEntityWithUUID(PUUID(), name);
    }

    // TODO  Replace Entity return with Entity Handle
    PEntity* PScene::CreateEntityWithUUID(pnt::PUUID uuid, const std::string& name) {
        // Add entity to Entity Registry
        auto entity = m_registry.Create(uuid, name);
        // Add ID Component
        auto id = entity->AddComponent<PIDComponent>();
        // Set ID
        id->setID(uuid);
        // Add Transform Component,
        entity->AddComponent<PTransformComponent>();
        // Add Tag Component
        auto tag = entity->AddComponent<PTagComponent>();
        // Add Entity to Entity Map
        PLog::echoMessage(LogLevel::Info, "%s %s %s", "Entity", "in Scene with ID:", static_cast<std::string>(id->m_entityInstanceID).c_str());
        return entity;
    }

    void PScene::DestroyEntity(PEntity* entity) {

    }

    void PScene::DestroyEntityWithUUID(pnt::PUUID uuid) {

    }

    PScene::PScene(const std::unordered_map<PUUID, PEntity *>& entityMap, const PEntityRegistry& registry) {

    }

    PScene::~PScene() {
        PLog::echoMessage("Destroying Scene.");
    }

}
