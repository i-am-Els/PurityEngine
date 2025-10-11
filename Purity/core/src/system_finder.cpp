//
// Created by Eniola Olawale on 9/7/2024.
//

#include "system_finder.h"
#include "ecs_service_conc.h"
#include "layer_service.h"
#include "layer_service_conc.h"
#include "papplication.h"
#include "renderer_service_conc.h"
#include "scene_layer.h"
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
        auto const layer = GetApplication()->serviceLocator->getService<ALayerService, PLayerService>()->fetchLayerByName(artifacts::builtInLayerNames["scene"]);
        auto const sceneLayer = dynamic_cast<scene::SceneLayer*>(layer);
        return sceneLayer != nullptr ? sceneLayer->getAttachedScene() : nullptr;
    }
}
