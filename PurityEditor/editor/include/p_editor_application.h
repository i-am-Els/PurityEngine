//
// Created by Eniola Olawale on 10/10/2024.
//

#pragma once
#define PURITY_ENTRY_POINT
#include "editor_pch.h"
#include "purity.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <optional>

using namespace commons;

using json = nlohmann::json;
using json_schema_validator = nlohmann::json_schema::json_validator;
using ordered_json = nlohmann::basic_json<nlohmann::ordered_map>;

using namespace purity;

namespace editor {
    struct DatabaseData {
        PUUID id;
        std::vector<std::map<std::string, std::string>> assets;
    };

    class PEditorApplication final : public PApplication{
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

        [[nodiscard]] std::optional<DatabaseData> validateDBFile() const;
        [[nodiscard]] bool validateSceneFile() const;
        [[nodiscard]] bool validateAssetFiles(const PUUID& id, const std::string& assetPath) const;
        static void reportInvalidAssets(const PUUID& file_id, const std::string& assetPath);
        void storeValidAssets(const PUUID& file_id, const std::string& assetPath);

    public:
        void preInit() override;
        void postInit() override;
        bool shouldClose(const WindowCloseEvent& event) override;
        void onEvent(Event& placeholder1) override;
    };

} // gui
