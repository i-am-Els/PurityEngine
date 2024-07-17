//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once
#include "window_pnt.h"
#include "service_locator.h"

using namespace pnt::graphics;
namespace pnt{

    class PApplication {
    protected:
        PApplication(const std::string &title, int width, int height) : applicationInfo(ApplicationInfo{title, width,
                                                                                                        height}) {
            serviceLocator = std::make_shared<PServiceLocator>();
        }

    public:
        std::unique_ptr<PWindow> window;

        virtual void init();
        virtual void start();
        virtual void process();
        virtual void update(float deltaTime);
        virtual void render();
        virtual void destroy();
        virtual void exit();

        std::shared_ptr<PServiceLocator> serviceLocator;

        struct ApplicationInfo{
            const std::string &title;
            int width;
            int height;
        } applicationInfo;
    };
}
