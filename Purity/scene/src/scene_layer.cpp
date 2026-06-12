//
// Created by Eniola Olawale on 11/10/2025.
//

#include "scene_layer.h"

//#include "papplication.h"
#include "assetdb_service_conc.h"
#include "time_manager.h"

using namespace purity::assetDB;

namespace purity::scene {
    void SceneLayer::render()
    {
        PLayer::render();
    }

    void SceneLayer::update()
    {
    }

    void SceneLayer::make_new_scene_asset(std::shared_ptr<PLevelAsset>& scene_asset, std::string relScenePathString)
    {
        // No default Scene was found, this is most likely(99%) a new project, Create one (A default scene file).
        auto _scene =  PScene::CreateDefaultScene();
        if (!switchScene(std::move(_scene))) { throw exceptions::NullPointerError("Scene::CreateDefaultScene() returned nullptr."); }

        // Better still rely on AssetDatabase to achieve this. Hoping it writes to DB on your behalf
        AssetRecord sceneRecord;
        sceneRecord.uuid = attached_scene->getID();
        sceneRecord.name = attached_scene->getName();
        sceneRecord.assetType = AssetType::LevelAsset;
        sceneRecord.representation = AssetRepresentation::Native;
        sceneRecord.metaPath = relScenePathString;   // points to the serialized scene file
        sceneRecord.sourcePath.reset();         // no external source
        sceneRecord.binaryPath.reset();         // no separate binary
        sceneRecord.isDirty = false;
        sceneRecord.isDeleted = false;
        sceneRecord.createdAt = commons::TimeManager::now_seconds();
        sceneRecord.modifiedAt = sceneRecord.createdAt;

        scene_asset = PAssetDatabase::queryDBForAsset(QuerySpec<PLevelAsset>(sceneRecord), QueryOperation::Write);
    }

    void RegisterProjectUpdate(const purity::PApplication::ProjectEditorInfo& editorInfo)
    {
        auto project_rel_path = commons::to_project_relative(editorInfo.projectFilePath, editorInfo.projectDir);
        if (!project_rel_path.has_value()) {
            throw exceptions::EmptyPathString();
        }
        auto project_record = PSystemFinder::GetAssetDatabase()->getAssetRecordFromRelPath(project_rel_path.value().string());
        auto project_file = assetDB::PAssetDatabase::queryDBForAsset(QuerySpec<PProjectAsset>(project_record, editorInfo.startUpSceneRelPath), QueryOperation::Update);
    }

    void SceneLayer::attached()
    {
        std::shared_ptr<PLevelAsset> scene_asset;
        const auto editorInfo = PSystemFinder::GetApplication()->m_projectEditorInfo;
        auto scenePathString = editorInfo.projectDir + "/" + editorInfo.startUpSceneRelPath;
        auto default_rel_scene_path = "Assets/Scenes/DefaultScene.pscene";

        if (editorInfo.startUpSceneRelPath.empty())
        {
            // CREATE SUBROUTINE
            // scenePathString = editorInfo.projectDir + "/" + default_rel_scene_path;
            make_new_scene_asset(scene_asset, default_rel_scene_path);
            // Register New scene as default start up scene.
            // This is a project file modification step
            PSystemFinder::GetApplication()->m_projectEditorInfo.startUpSceneRelPath = default_rel_scene_path;
            // therefore we have to update and save the project file.
            RegisterProjectUpdate(editorInfo);
        }
        else
        {
            fs_path scenePath(scenePathString);
            if (!_validateFileExistence(scenePath)){ throw exceptions::FileReadError(scenePathString.c_str()); }

            // File Exists Read it into Memory.
            const auto sceneRecord = PSystemFinder::GetAssetDatabase()->getAssetRecordFromRelPath(editorInfo.startUpSceneRelPath);
            scene_asset = assetDB::PAssetDatabase::queryDBForAsset(QuerySpec<PLevelAsset>(sceneRecord),
                                                                   QueryOperation::Read);
            if (scene_asset == nullptr)
            {
                // GO over the creation subroutine
                make_new_scene_asset(scene_asset, editorInfo.startUpSceneRelPath);
                // Register New scene as default start up scene.
                // This is a project file modification step
                PSystemFinder::GetApplication()->m_projectEditorInfo.startUpSceneRelPath = default_rel_scene_path;
                // therefore we have to update and save the project file.
                RegisterProjectUpdate(editorInfo);
            }
        }
        if (scene_asset == nullptr)
        {
            throw exceptions::NullPointerError("Failed to resolve a scene asset.");
        }

        // auto loaded_scene = scene_asset->loadScene();
        // if (!switchScene(std::move(loaded_scene)))
        // {
        //     throw exceptions::NullPointerError("Failed to attach scene.");
        // }
    }

    void SceneLayer::detached()
    {
    }

    void SceneLayer::eventFired(Event& event)
    {
    }

    bool SceneLayer::switchScene(std::unique_ptr<scene::PScene> scene)
    {
        if(scene == nullptr) { return false;}
        const auto temp = std::move(attached_scene);
        attached_scene = std::move(scene);
        return true;
    }
} // scene
// purity