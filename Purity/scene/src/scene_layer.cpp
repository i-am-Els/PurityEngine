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

    /// <summary>
    ///  This method makes a new scene obj, swaps it into the SceneLayer's attachedScene, and creates a record for this new scene which it pushes into persistent file storage and to the Database. 
    /// <para>
    ///   The method is marked "tc" meaning it should be used in a try-catch block since it throws an exception. 
    /// </para>
    /// </summary>
    /// <param name="scene_asset"></param>
    /// <param name="relScenePathString"></param>
    void purity::scene::SceneLayer::MakeNewSceneAsset_TC(std::shared_ptr<PLevelAsset>& scene_asset, std::string relScenePathString)
    {
        auto _scene = PScene::CreateNewScene("DefaultScene");
        auto switched = switchScene(std::move(_scene));
        // No default Scene was found, this is most likely(99%) a new project, Create one (A default scene file).
        if (!switched) { throw exceptions::NullPointerError("Scene::CreateNewScene() returned nullptr."); }

        // Better still rely on AssetDatabase to achieve this. Hoping it writes to DB on your behalf
        AssetRecord sceneRecord;
        sceneRecord.uuid = commons::PUUID();
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

        attached_scene->setSourceAssetUUID(sceneRecord.uuid);

        scene_asset = PAssetDatabase::queryDBForAsset(QuerySpec<PLevelAsset>(sceneRecord), QueryOperation::Write);
    }

    void SceneLayer::attached()
    {
        std::shared_ptr<PLevelAsset> scene_asset;
        const auto& editorInfo = PSystemFinder::GetApplication()->m_projectEditorInfo;
        auto scenePathString = editorInfo.projectDir + "/" + editorInfo.startUpSceneRelPath;
        auto default_rel_scene_path = "Assets/Scenes/DefaultScene.pscene";

		commons::PLog::echoMessage(LogLevel::Info, "SceneLayer::attached() - Scene File to attach: %s", scenePathString.c_str());

        fs_path scenePath(scenePathString);
        try
        {
			bool fileExists = commons::_validateFileExistence(scenePath);
            if (!fileExists)
            {
			    // CREATE NEW SCENE FILE SINCE STARTUP SCENE DOES NOT EXIST
				commons::PLog::echoMessage(LogLevel::Info, "SceneLayer::attached() - Startup Scene does not exist, creating new scene file at: %s", default_rel_scene_path);
                // scenePathString = editorInfo.projectDir + "/" + default_rel_scene_path;
                MakeNewSceneAsset_TC(scene_asset, default_rel_scene_path);
                // Register New scene as default start up scene.
                // This is a project file modification step
                PSystemFinder::GetApplication()->m_projectEditorInfo.startUpSceneRelPath = default_rel_scene_path;
                // therefore we have to update and save the project file.
                PAssetDatabase::RegisterProjectUpdate(editorInfo);
            }

            // File Exists Read it into Memory.
            const auto sceneRecord = PSystemFinder::GetAssetDatabase()->getAssetRecordFromRelPath(editorInfo.startUpSceneRelPath);
			if (!sceneRecord.has_value())
			{
				commons::PLog::echoMessage(LogLevel::Info, "SceneLayer::attached() - No Asset Record found for scene file: %s", editorInfo.startUpSceneRelPath.c_str());
				throw exceptions::NullPointerError("No Asset Record found for scene file.");
			}
            
            if(fileExists) 
            {
                scene_asset = assetDB::PAssetDatabase::queryDBForAsset(QuerySpec<PLevelAsset>(sceneRecord.value()),QueryOperation::Read);
            }
            if (scene_asset == nullptr)
            {
                throw exceptions::NullPointerError("Failed to resolve a scene asset.");
            }
        }
		catch (std::exception& e)
		{
			commons::PLog::echoMessage(commons::LogLevel::Error, "SceneLayer::attached() - Exception: %s", e.what());
			/*throw;*/
		}

        /*if (!switchScene(std::move(loaded_scene)))
        {
            throw exceptions::NullPointerError("Failed to attach scene.");
        }*/
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
        const auto& temp = std::move(attached_scene);
        attached_scene = std::move(scene);
        return true;
    }
} // scene
// purity