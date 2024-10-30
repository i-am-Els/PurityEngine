//
// Created by Eniola Olawale on 9/7/2024.
//

#pragma once

#include "iservices.h"
#include "isystems.h"


namespace pnt{
    namespace scene {
        class PScene;
    }
    class PApplication;
    class PWindow;
    class PServiceLocator;
    class PECSService;

    class PNT_API PSystemFinder {
        friend PApplication;
    public:
        static PSystemFinder& GetInstance(){
            static PSystemFinder instance;
            return instance;
        }

        static PApplication *GetApplication();

        static PWindow *GetWindow();

        static scene::PScene *GetScene();

        static PECSService * GetECSService();

        static std::shared_ptr<PServiceLocator> GetServiceLocator();

    private:
        static PApplication* application;
    };

}
