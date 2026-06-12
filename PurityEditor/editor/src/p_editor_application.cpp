//
// Created by Eniola Olawale on 10/10/2024.
//

#include "p_editor_application.h"

#include "editors.h"
#include "editor_layer.h"
#include <fstream>

#include "content_index.h"
#include "game_layer.h"
#include "layer_service.h"
#include "layer_service_conc.h"
using namespace commons;
using namespace purity;

namespace editor {

    bool PEditorApplication::verify() {
        return validate_db_file_and_collect_valid_db_records();

    }

    fs_path PEditorApplication::get_DB_file_path()
    {
        std::cout << "Testing:: " << m_projectEditorInfo.projectDir << std::endl;
        fs_path pDBfilePath = fs_path(m_projectEditorInfo.projectDir) / "Assets" / (m_applicationInfo.title + ".peDB");
        return pDBfilePath;
    }

    bool PEditorApplication::validate_db_file_and_collect_valid_db_records()
    {
        // Build the expected DB file path.
        fs_path pDBfilePath = get_DB_file_path();

        if (!commons::_validateFileExistence(pDBfilePath)) { return false; }

        try {
            // Open database file.
            Database db;
            if (!db.create_or_open_db(pDBfilePath))
            {
                return false;
            }

            DatabaseData dbData = db.readAllAssets(
                [&](const AssetRecord& asset)
                {
                    if (!validateAssetFiles(asset.uuid, asset.metaPath.string()))
                    {
                        reportInvalidAssets(asset.uuid, asset.metaPath.string());
                        return false;
                    }

                    if (asset.binaryPath &&
                        !validateAssetFiles(asset.uuid, asset.binaryPath.value().string()))
                    {
                        reportInvalidAssets(asset.uuid, asset.binaryPath.value().string());
                        return false;
                    }

                    storeValidAssets(asset.uuid, asset);
                    return true;
                });
            if (dbData.empty())
            {
                return false;
            }
            return true;
        }
        catch(const std::exception& e){
            // Log the exception message if needed.
            std::cerr << "Error parsing DB file: " << e.what() << std::endl;
            return false;
        }
    }

    bool PEditorApplication::validateSceneFile() const
    {
        std::filesystem::path pscenefilePath = std::filesystem::path(m_projectEditorInfo.projectDir) / m_projectEditorInfo.startUpSceneRelPath;
        if (!commons::_validateFileExistence(pscenefilePath) || !commons::_validateSchemaAdherence(pscenefilePath.string(), commons::pAssetSchema)) { return false; }
        return true;
    }

    bool PEditorApplication::validateAssetFiles(const PUUID& id, const std::string& assetPath) const
    {
        if (!id) { return false; }
        std::filesystem::path assetfilePath = std::filesystem::path(m_projectEditorInfo.projectDir) / assetPath;
        // figure out if asset is a pproject and use a different schema
        if (commons::is_project_file(assetfilePath))
        {
            if (!commons::_validateFileExistence(assetfilePath) || !commons::_validateSchemaAdherence((assetfilePath.string()), commons::pProjectSchema)) { return false; }
            return true;
        }

        if (!commons::_validateFileExistence(assetfilePath) || !commons::_validateSchemaAdherence((assetfilePath.string()), commons::pAssetSchema)) { return false; }
        return true;
    }

    void PEditorApplication::reportInvalidAssets(const PUUID& file_id, const std::string& assetPath)
    {
        PLog::echoMessage(LogLevel::Warning, "%s %s %s %s %s", "Asset of id", static_cast<std::string>(file_id).c_str(), "at", assetPath.c_str(), "is not valid, hence removed from asset database.");
    }

    void PEditorApplication::storeValidAssets(const PUUID& asset_id, const AssetRecord& asset_record)
    {
        // Do not add the Project file into the assetDBData map... that map represents the
        if (asset_record.assetType == AssetType::ProjectAsset){ 

            return; 
        }
        PLog::echoMessage(LogLevel::Info, "%s %s %s %s %s", "Adding asset of id", static_cast<std::string>(asset_id).c_str(), "and path:", asset_record.metaPath.string().c_str(), "to the queue going to the asset database.");
        assetdbData[asset_id] = asset_record;
    }

    void PEditorApplication::preInit()
    {
        PApplication::preInit();
    }

    void PEditorApplication::postInit()
    {
        PApplication::postInit();
    }

    bool PEditorApplication::shouldClose(const WindowCloseEvent& event)
    {
        return PApplication::shouldClose(event);
    }

    void PEditorApplication::onEvent(Event& placeholder1)
    {
        PApplication::onEvent(placeholder1);
    }

    PEditorApplication::~PEditorApplication() {
        PLog::echoMessage("Deleting PEditorApplication");
    }

    void PEditorApplication::init() {
        PApplication::init();
        const auto layer_service = serviceLocator->getService<ALayerService, PLayerService>();
        const auto uiLayerID = layer_service->PushOverlay(new gui::EditorLayer(purity::artifacts::builtInLayerNames["ui"]));
        const auto editor = dynamic_cast<gui::EditorLayer*>(layer_service->getLayerByPUUID(uiLayerID));
        gui::EditorLayer::setupEditor(editor);

        const auto gameLayerID = layer_service->PushLayer(new editor::layers::GameLayer(purity::artifacts::builtInLayerNames["game"]));
    }

    void PEditorApplication::start() {
        PApplication::start();
    }

    void PEditorApplication::process() {
        PApplication::process();
    }

    void PEditorApplication::update(float deltaTime) {
        PApplication::update(deltaTime);
    }

    void PEditorApplication::render() {
        PApplication::render();
    }

    void PEditorApplication::destroy() {
        PApplication::destroy();
    }

    void PEditorApplication::exit() {
        PApplication::exit();
    }

    PEditorApplication::PEditorApplication() : PApplication() {
    }
} // gui



purity::PApplication* purity::CreateApplication(){
    return new editor::PEditorApplication();
}
