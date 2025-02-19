//
// Created by Eniola Olawale on 10/10/2024.
//

#pragma once
#define PURITY_ENTRY_POINT
#include "purity.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <optional>

using namespace commons;

using json = nlohmann::json;
using json_schema_validator = nlohmann::json_schema::json_validator;
using ordered_json = nlohmann::basic_json<nlohmann::ordered_map>;

using namespace purity;

namespace gui {
    struct DatabaseData {
        PUUID id;
        std::vector<std::map<std::string, std::string>> assets;
    };

    class PEditorApplication : public PApplication{
    public:
        PEditorApplication();

        ~PEditorApplication() override;

        void init() override;

        void start() override;

        void process() override;

        void update(float deltaTime) override;

        void render() override;

        void destroy() override;

        void exit() override;

        bool verify() override;

    private:
        std::map<PUUID, std::string> assetdbData;

        std::optional<DatabaseData> validateDBFile();
        bool validateSceneFile();
        bool validateAssetFiles(PUUID id, const std::string& assetPath);
        void reportInvalidAssets(PUUID file_id, const std::string& assetPath);
        void storeValidAssets(PUUID file_id, const std::string& assetPath);
    };

} // gui
