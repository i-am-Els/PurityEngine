//
// Created by Eniola Olawale on 10/10/2024.
//

#pragma once
#define PURITY_ENTRY_POINT
#include "purity.h"

using namespace purity;

namespace gui {

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
        std::pair<bool, std::map<PUUID, std::string>> validateDBFile();
        bool validateSceneFile();
        bool validateAssetFiles(const std::string& asset);
        void reportInvalidAssets(PUUID file_id);
    };

} // gui
