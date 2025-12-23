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

    void SceneLayer::attached()
    {
        std::shared_ptr<PLevelAsset> scene_asset;
        const auto editorInfo = PSystemFinder::GetApplication()->m_projectEditorInfo;
        auto scenePathString = editorInfo.projectDir + "/" + editorInfo.startUpSceneRelPath;

        if (editorInfo.startUpSceneRelPath.empty())
        {
            // CREATE SUBROUTINE
            scenePathString = editorInfo.projectDir + "/" + "Assets/Scenes/DefaultScene.pscene";
            // No default Scene was found, this is most likely(99%) a new project, Create one(A default scene file).
            auto _scene =  PScene::CreateDefaultScene();
            if (!switchScene(std::move(_scene))) { throw exceptions::NullPointerError("Scene::CreateDefaultScene() returned nullptr."); }

            // Better still rely on AssetDatabase to achieve this. Hoping it writes to DB on your behalf
            AssetRecord sceneRecord;
            sceneRecord.uuid = getAttachedScene()->getID();
            sceneRecord.name = getAttachedScene()->getName();
            sceneRecord.assetType = AssetType::LevelAsset;
            sceneRecord.representation = AssetRepresentation::Native;
            sceneRecord.metaPath = scenePathString;   // points to the serialized scene file
            sceneRecord.sourcePath.reset();         // no external source
            sceneRecord.binaryPath.reset();         // no separate binary
            sceneRecord.isDirty = false;
            sceneRecord.isDeleted = false;
            sceneRecord.createdAt = TimeManager::now_seconds();
            sceneRecord.modifiedAt = sceneRecord.createdAt;

            scene_asset = assetDB::PAssetDatabase::queryDBForAsset(QuerySpec<PLevelAsset>(sceneRecord), QueryOperation::Write);
        }
        else
        {
            fs_path scenePath(scenePathString);
            if (!_validateFileExistence(scenePath)){ throw exceptions::FileReadError(scenePathString.c_str()); }
            // TODO: File Exists Read it into Memory.
            // TODO How do i get asset records here from just rel path?
            scene_asset = assetDB::PAssetDatabase::queryDBForAsset(QuerySpec<PLevelAsset>(), QueryOperation::Read);
            if (scene_asset == nullptr)
            {
                // GO over the creation sub-routine
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