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
    std::shared_ptr<PWindow> PSystemFinder::window = nullptr;
    scene::PScene* PSystemFinder::scene = nullptr;
    PECSService* PSystemFinder::ecsService = nullptr;
    graphics::PRendererService* PSystemFinder::rendererService = nullptr;
    std::shared_ptr<PServiceLocator> PSystemFinder::serviceLocator = nullptr;

    PApplication *PSystemFinder::GetApplication() {
        return application;
    }

    PECSService *PSystemFinder::GetECSService() {
        if (ecsService == nullptr)
        {
            ecsService = GetApplication()->serviceLocator->getService<AECSService, PECSService>().get();
        }
        return ecsService;
    }

    PRendererService* PSystemFinder::GetRendererService()
    {
        if (rendererService == nullptr)
        {
            rendererService = GetApplication()->serviceLocator->getService<ARendererService, PRendererService>().get();
        }
        return rendererService;
    }

    std::shared_ptr<PServiceLocator> PSystemFinder::GetServiceLocator() {
        if (serviceLocator == nullptr)
        {
            serviceLocator = GetApplication()->serviceLocator;
        }
        return serviceLocator;
    }

    std::shared_ptr<PWindow>& PSystemFinder::GetWindow()
    {
        if (window == nullptr)
        {
            window = GetApplication()->window;
        }
        return window;
    }

    scene::PScene *PSystemFinder::GetScene() {
        if (scene == nullptr)
        {
            auto const layer = GetApplication()->serviceLocator->getService<ALayerService, PLayerService>()->fetchLayerByName(artifacts::builtInLayerNames["scene"]);
            auto const sceneLayer = dynamic_cast<scene::SceneLayer*>(layer);
            scene = sceneLayer != nullptr ? sceneLayer->getAttachedScene() : nullptr;
        }
        return scene;
    }
}
