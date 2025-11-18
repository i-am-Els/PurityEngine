//
// Created by Eniola Olawale on 10/10/2024.
//

#include "p_editor_application.h"

#include "editors.h"
#include "editor_layer.h"
#include "fstream"
#include "game_layer.h"
#include "layer_service.h"
#include "layer_service_conc.h"
using namespace commons;
using namespace purity;

namespace editor {

    bool PEditorApplication::verify() {
        std::optional<DatabaseData> dbData = validateDBFile();
        if (!dbData.has_value()) { return false; }
        if (!validateSceneFile()) { return false; }
        auto assetDB_arr = dbData.value();
        if (!assetDB_arr.assets.empty())
        {
            for (const auto& map_ : assetDB_arr.assets) {
                PUUID id = PUUID::fromString(map_.at("id"));
                if (!validateAssetFiles(id, map_.at("path"))) { 
                    reportInvalidAssets(id, map_.at("path"));
                    continue;
                }
                storeValidAssets(id, map_.at("path"));
            }
        }
        return true;
    }

    std::optional<DatabaseData> PEditorApplication::validateDBFile() const
    {
        // Build the expected DB file path.
        std::cout << "Testing:: " << m_projectEditorInfo.projectDir << std::endl;
        std::filesystem::path pDBfilePath = std::filesystem::path(m_projectEditorInfo.projectDir) / "Assets" / (m_applicationInfo.title + ".peDB");

        if (!commons::_validateFileExistence(pDBfilePath) || !commons::_validateSchemaAdherence(pDBfilePath.string(), commons::pDatabaseSchema)) { return std::nullopt; }
        
        try {
            std::ifstream data(pDBfilePath);
            if (!data) { return std::nullopt; }
            json data_json;
            data >> data_json;

            // Build the result data structure.
            DatabaseData dbData;
            dbData.id = commons::PUUID::fromString(data_json["id"].get<std::string>());

            // Assuming data_json["assets"] is an array of objects,
            // where each object is convertible to std::map<std::string, std::string>.
            dbData.assets = data_json["assets"].get<std::vector<std::map<std::string, std::string>>>();

            return dbData;
        }
        catch(const std::exception& e){
            // Log the exception message if needed.
            std::cerr << "Error parsing DB file: " << e.what() << std::endl;
            return std::nullopt;
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
        if (!commons::_validateFileExistence(assetfilePath) || !commons::_validateSchemaAdherence(assetfilePath.string(), commons::pAssetSchema)) { return false; }
        return true;
    }

    void PEditorApplication::reportInvalidAssets(const PUUID& file_id, const std::string& assetPath)
    {
        PLog::echoMessage(LogLevel::Warning, "%s %s %s %s %s", "Asset of id", static_cast<std::string>(file_id).c_str(), "at", assetPath.c_str(), "is not valid, hence removed from asset database.");
    }

    void PEditorApplication::storeValidAssets(const PUUID& file_id, const std::string& assetPath)
    {
        PLog::echoMessage(LogLevel::Info, "%s %s %s %s %s", "Adding asset of id", static_cast<std::string>(file_id).c_str(), "and path:", assetPath.c_str(), "to the queue going to the asset database.");
        assetdbData[file_id] = assetPath;
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
