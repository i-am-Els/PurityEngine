//
// Created by Eniola Olawale on 9/7/2024.
//

#pragma once

#include "iservices.h"
#include "isystems.h"

namespace pnt{
    class PApplication;
    class PServiceLocator;
    class PECSService;

    class PSystemFinder {
        friend PApplication;
    public:
        static PSystemFinder& GetInstance(){
            static PSystemFinder instance;
            return instance;
        }

        static PApplication *GetApplication();

        static PECSService * PGetECSService();

        static std::shared_ptr<PServiceLocator> GetServiceLocator();

    private:
        static PApplication* application;
    };

}
