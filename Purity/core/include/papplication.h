//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "service_locator.h"
#include "window_purity.h"
#include "scene.h"

namespace purity{

    class PURITY_API PApplication {
    protected:
        PApplication(std::string title, int width, int height);

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

        std::shared_ptr<PServiceLocator> serviceLocator;
        scene::PScene Scene{};

        struct PURITY_API ApplicationInfo{
            std::string title;
            int width;
            int height;

            ApplicationInfo(std::string t, int w, int h){
                title = t;
                width = w;
                height = h;
            }
        };

        ApplicationInfo applicationInfo;
    };

    // To be defined in client code
    PURITY_API PApplication* CreateApplication();
}
