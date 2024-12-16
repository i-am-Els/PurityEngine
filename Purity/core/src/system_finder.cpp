//
// Created by Eniola Olawale on 9/7/2024.
//

#include "system_finder.h"
#include "papplication.h"
#include "service_locator.h"
#include "ecs_service_conc.h"
#include "scene.h"

namespace purity{
    PApplication* PSystemFinder::application = nullptr;

    PApplication *PSystemFinder::GetApplication() {
        return application;
    }

    PECSService *PSystemFinder::GetECSService() {
        return dynamic_cast<PECSService *>(GetApplication()->serviceLocator->getService<IECSService>().get());
    }

    std::shared_ptr<PServiceLocator> PSystemFinder::GetServiceLocator() {
        return GetApplication()->serviceLocator;
    }

    PWindow *PSystemFinder::GetWindow() {
        return GetApplication()->window.get();
    }

    scene::PScene *PSystemFinder::GetScene() {
        return &GetApplication()->Scene;
    }
}
