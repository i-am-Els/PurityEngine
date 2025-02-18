//
// Created by Eniola Olawale on 10/10/2024.
//

#include "p_editor_application.h"

namespace gui {

    bool PEditorApplication::verify() {
        auto assets = validateDBFile();
        if (!assets.first) { return false; }
        if (!validateSceneFile()) { return false; }
        if (!assets.second.empty())
        {
            for (const auto& pair : assets.second) {
                if (!validateAssetFiles(pair.second)) { reportInvalidAssets(pair.first); }
            }
        }
        return true;
    }

    std::pair<bool, std::map<PUUID, std::string>> PEditorApplication::validateDBFile()
    {
        return std::pair(false, std::map<PUUID, std::string>());
    }

    bool PEditorApplication::validateSceneFile()
    {
        return false;
    }

    bool PEditorApplication::validateAssetFiles(const std::string& asset)
    {
        return false;
    }

    void PEditorApplication::reportInvalidAssets(PUUID file_id)
    {
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
