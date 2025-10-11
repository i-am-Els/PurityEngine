//
// Created by Eniola Olawale on 9/17/2024.
//

#include "scene.h"

#include "assetdb_service_conc.h"
#include "tag_comp.h"
#include "id_comp.h"
#include "system_finder.h"
#include "service_locator.h"


namespace purity::scene{

    PEntityHandle PScene::CreateEntity(const std::string &name) {
        return CreateEntityWithUUID(PUUID(), name);
    }

    PEntityHandle PScene::CreateEntityWithUUID(commons::PUUID uuid, const std::string& name) {
        // Add entity to Entity Registry
        auto entity = m_registry.Create(uuid, name);
        // Add ID Component
        auto id = entity.AddComponent<PIDComponent>();
        // Set ID
        id->setID(uuid);
        // Add Transform Component,
        entity.AddComponent<PTransformComponent>();
        // Add Tag Component
        auto tag = entity.AddComponent<PTagComponent>();
        // Add Entity to Entity Map
        PLog::echoMessage(LogLevel::Info, "%s %s %s", "Entity", "in Scene with ID:", static_cast<std::string>(id->m_entityInstanceID).c_str());
        return entity;
    }

    void PScene::DestroyEntity(PEntityHandle entity) {
        m_registry.Destroy(entity.getInstanceID());
    }

    void PScene::DestroyEntityWithUUID(commons::PUUID uuid) {
        m_registry.Destroy(uuid);
    }

    PScene::PScene() = default;

    PScene::~PScene() {
        // TODO - clear out all systems and there components during scene switch
        PLog::echoMessage("Destroying Scene.");
    }

    bool PScene::HasAnythingToRender() {
        return !PSystemFinder::GetScene()->m_registry.entityMapIsEmpty();
    }

    PScene* PScene::LoadScene(const PUUID& scene_id)
    {
        PScene* scene;
        if (static_cast<int>(scene_id) != 0)
        {
            // TODO - Start Serializing from json using Cereal.
            // auto scene_asset = PSystemFinder::GetServiceLocator()->getService<AAssetDBService, assetDB::PAssetDatabase>()->
            // queryDBForAsset<assetDB::PLevelAsset>(assetDB::QueryLevelAssetSpec(scene_id), assetDB::QueryOperation::Read);
            // scene = scene_asset.get();
            // return scene;
        }
        // TODO - create a new asset file repressenting this asset in asset DB
        scene = new PScene();
        auto bunny = scene->CreateEntity("Bunny");

        auto mesh = bunny.AddComponent<PMeshComponent>();
        auto render = bunny.AddComponent<PRenderComponent>();

        PLog::echoValue(bunny.GetComponent<PTransformComponent>()->m_position);

        return scene;
    }

    PScene* PScene::UnloadScene()
    {
        return nullptr;
    }
}
