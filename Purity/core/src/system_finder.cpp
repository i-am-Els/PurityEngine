//
// Created by Eniola Olawale on 9/7/2024.
//

#include "system_finder.h"
#include "ecs_service_conc.h"
#include "papplication.h"
#include "renderer_service_conc.h"
#include "service_locator.h"


namespace purity{
    PApplication* PSystemFinder::application = nullptr;

    PApplication *PSystemFinder::GetApplication() {
        return application;
    }

    PECSService *PSystemFinder::GetECSService() {
        return GetApplication()->serviceLocator->getService<AECSService, PECSService>().get();
    }

    PRendererService* PSystemFinder::GetRendererService()
    {
        return GetApplication()->serviceLocator->getService<ARendererService, PRendererService>().get();
    }

    std::shared_ptr<PServiceLocator> PSystemFinder::GetServiceLocator() {
        return GetApplication()->serviceLocator;
    }

    std::shared_ptr<PWindow>& PSystemFinder::GetWindow() {
        return GetApplication()->window;
    }

    scene::PScene *PSystemFinder::GetScene() {
        return GetApplication()->Scene;
    }
}
