//
// Created by Eniola Olawale on 11/10/2025.
//

#include "scene_layer.h"

#include "papplication.h"
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
        // No default Scene was found, this is most likely(99%) a new project, Create one(A default scene file).
        auto _scene =  PScene::CreateDefaultScene();
        if (!switchScene(std::move(_scene))) { throw exceptions::NullPointerError("Scene::CreateDefaultScene() returned nullptr."); }

        // Better still rely on AssetDatabase to achieve this. Hoping it writes to DB on your behalf
        AssetRecord sceneRecord;
        sceneRecord.uuid = _scene->getID();
        sceneRecord.name = _scene->getName();
        sceneRecord.assetType = AssetType::LevelAsset;
        sceneRecord.representation = AssetRepresentation::Native;
        sceneRecord.metaPath = relScenePathString;   // points to the serialized scene file
        sceneRecord.sourcePath.reset();         // no external source
        sceneRecord.binaryPath.reset();         // no separate binary
        sceneRecord.isDirty = false;
        sceneRecord.isDeleted = false;
        sceneRecord.createdAt = TimeManager::now_seconds();
        sceneRecord.modifiedAt = sceneRecord.createdAt;

        scene_asset = assetDB::PAssetDatabase::queryDBForAsset(QuerySpec<PLevelAsset>(sceneRecord), QueryOperation::Write);
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
                // GO over the creation sub-routine
                make_new_scene_asset(scene_asset, editorInfo.startUpSceneRelPath);
            }
        }

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