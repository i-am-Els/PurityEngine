//
// Created by Eniola Olawale on 9/17/2024.
//

#include "scene.h"
#include "entity_handle.h"

#include "assetdb_service_conc.h"
#include "service_locator.h"
#include "system_finder.h"
#include "tag_comp.h"


namespace purity::scene{

    PEntityHandle PScene::CreateEntity(const std::string &name) {
        return CreateEntityWithUUID(PUUID(), name);
    }

    PEntityHandle PScene::CreateEntityWithUUID(commons::PUUID uuid, const std::string& name) {
        // Add entity to Entity Registry
        auto entityHandle = m_registry.Create(uuid, name);

        // Add Transform Component,
        entityHandle.AddComponent<PTransformComponent>();
        // Add Tag Component
        auto tag = entityHandle.AddComponent<PTagComponent>();
        // Add Entity to Entity Map

        PLog::echoMessage(LogLevel::Info, "%s %s %s", "Entity", "in Scene with ID:", PUUID::to_string(entityHandle.getInstanceID()).c_str());
        return entityHandle;
    }

    void PScene::DestroyEntity(PEntityHandle entityHandle) {
        m_registry.Destroy(entityHandle.getInstanceID());
        /// TODO : Dont forget to remove from Sparse Set
    }

    void PScene::DestroyEntityWithUUID(commons::PUUID uuid) {
        m_registry.Destroy(uuid);
        /// TODO : Dont forget to remove from Sparse Set
    }

    PScene::PScene() : m_scene_id(PUUID()), m_registry(this), m_ecsService(this) {
        m_ecsService.initialize();
    }

    PScene::PScene(const PUUID& id) : m_scene_id(id), m_registry(this), m_ecsService(this)
    {
        m_ecsService.initialize();
    }

    PScene::~PScene() {
        // TODO - clear out all ecs services' pool managers and there components during scene switch
        m_ecsService.destroy();
        PLog::echoMessage("Destroying Scene.");
    }

    bool PScene::hasAnythingToRender() {
        return !m_registry.entityMapIsEmpty(); // TODO - Change this method to check if any object with an `enabled` render component is present in the scene
    }

    std::unique_ptr<PScene> PScene::LoadScene(const std::string& scene_asset_rel_path)
    {
        
        std::unique_ptr<PScene> scene; 
        std::shared_ptr<assetDB::PLevelAsset> scene_asset;

        fs_path scenePath(scene_asset_rel_path);
        try
        {
            bool fileExists = commons::_validateFileExistence(scenePath);
            if (!fileExists)
            {
                throw exceptions::FileReadError("Scene file missing or simply does note exist!");
            }

            // File Exists Read it into Memory.
            const auto sceneRecord = PSystemFinder::GetAssetDatabase()->getAssetRecordFromRelPath(scene_asset_rel_path);
            if (!sceneRecord.has_value())
            {
                commons::PLog::echoMessage(LogLevel::Info, "Scene::LoadScene() - No Asset Record found for scene file: %s", scene_asset_rel_path.c_str());
                throw exceptions::NullPointerError("No Asset Record found for scene file.");
            }

            scene_asset = assetDB::PAssetDatabase::queryDBForAsset(assetDB::QuerySpec<assetDB::PLevelAsset>(sceneRecord.value()), QueryOperation::Read);
            
            if (scene_asset == nullptr)
            {
                throw exceptions::NullPointerError("Failed to resolve a scene asset.");
            }


            /// TODO - BUILD SCENE FROM SCENE ASSET FILE
            /*if (!switchScene(std::move(loaded_scene)))
            {
                throw exceptions::NullPointerError("Failed to attach scene.");
            }*/
        }
        catch (std::exception& e)
        {
            commons::PLog::echoMessage(commons::LogLevel::Error, "Scene::LoadScene() - Exception: %s", e.what());
            return nullptr;
            /*throw;*/
        }


        return scene;
    }

    std::unique_ptr<PScene> PScene::CreateNewScene(const std::string& scene_name)
    {
        std::unique_ptr<PScene> scene = std::make_unique<PScene>();
        scene->setName(scene_name);
        PEntityHandle bunny = scene->CreateEntity("Bunny");

        auto mesh = bunny.AddComponent<PMeshComponent>();
        auto render = bunny.AddComponent<PRendererComponent>();

        const auto bunny_transform = fetch_or_throw(bunny.GetComponent<PTransformComponent>());
        PLog::echoValue(bunny_transform->m_position);

        return scene;
    }

    void PScene::UnloadScene()
    {
        // TODO: Replace with actual unload logic
    }
}
