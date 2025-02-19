//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "service_locator.h"
#include "window_purity.h"
#include "scene.h"
#include "events.h"

#include <filesystem>

namespace purity{

    class PURITY_API PApplication {
    protected:
        PApplication();

    public:
        std::unique_ptr<PWindow> window;

        virtual ~PApplication() {
            PLog::echoMessage("Destroying PApplication.");
        }
        virtual void init();
        virtual void start();
        virtual void process();
        virtual void update(float deltaTime);
        virtual void render();
        virtual void destroy();
        virtual void exit();
        virtual void shouldClose();
        virtual bool verify();

        virtual void onEvent(Event& event);

        std::shared_ptr<PServiceLocator> serviceLocator;
        scene::PScene Scene{};

        struct PURITY_API ApplicationInfo{
            std::string title;
            int width;
            int height;

            ApplicationInfo(){}

            ApplicationInfo(std::string t, int w, int h){
                title = t;
                width = w;
                height = h;
            }
        };

        struct PURITY_API ProjectEditorInfo {
            std::string projectFilePath;
            std::string projectDir;
            std::string startUpSceneRelPath;

            ProjectEditorInfo(){}

            ProjectEditorInfo(std::string _projectFilePath, std::string _startUpScene) {
                projectFilePath = _projectFilePath;
                projectDir = std::filesystem::path(projectFilePath).parent_path().string();
                startUpSceneRelPath = _startUpScene;
            }

            std::string getProjectName() {
                return std::filesystem::path(projectFilePath).stem().string();
            }
        };

        ApplicationInfo m_applicationInfo;
        ProjectEditorInfo m_projectEditorInfo;
    };

    // To be defined in client code
    PURITY_API PApplication* CreateApplication();
}
