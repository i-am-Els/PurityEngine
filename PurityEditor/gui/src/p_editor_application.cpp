//
// Created by Eniola Olawale on 10/10/2024.
//

#include "p_editor_application.h"
#include "fstream"
using namespace commons; 

namespace gui {

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

    std::optional<DatabaseData> PEditorApplication::validateDBFile()
    {
        // Build the expected DB file path.
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

    bool PEditorApplication::validateSceneFile()
    {
        std::filesystem::path pscenefilePath = std::filesystem::path(m_projectEditorInfo.projectDir) / m_projectEditorInfo.startUpSceneRelPath;
        if (!commons::_validateFileExistence(pscenefilePath) || !commons::_validateSchemaAdherence(pscenefilePath.string(), commons::pAssetSchema)) { return false; }
        return true;
    }

    bool PEditorApplication::validateAssetFiles(PUUID id, const std::string& assetPath)
    {
        if (!id) { return false; }
        std::filesystem::path assetfilePath = std::filesystem::path(m_projectEditorInfo.projectDir) / assetPath;
        if (!commons::_validateFileExistence(assetfilePath) || !commons::_validateSchemaAdherence(assetfilePath.string(), commons::pAssetSchema)) { return false; }
        return true;
    }

    void PEditorApplication::reportInvalidAssets(PUUID file_id, const std::string& assetPath)
    {
        PLog::echoMessage(LogLevel::Warning, "%s %s %s %s %s", "Asset of id", static_cast<std::string>(file_id).c_str(), "at", assetPath.c_str(), "is not valid, hence removed from asset database.");
    }

    void PEditorApplication::storeValidAssets(PUUID file_id, const std::string& assetPath)
    {
        PLog::echoMessage(LogLevel::Info, "%s %s %s %s %s", "Adding asset of id", static_cast<std::string>(file_id).c_str(), "and path:", assetPath.c_str(), "to the queue going to the asset database.");
        assetdbData[file_id] = assetPath;
    }

    PEditorApplication::~PEditorApplication() {
        PLog::echoMessage("Deleting PEditorApplication");
    }

    void PEditorApplication::init() {
        PApplication::init();
        
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
    return new gui::PEditorApplication();
}
