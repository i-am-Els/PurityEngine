//
// Created by Eniola Olawale on 9/17/2023.
//


/* *************************************************************************************
 *                                 Police and Thief Game
 * *************************************************************************************
 *
 * Two entities, Yourself and the AI.
 * Roles: 1. Police - Find the Thief.
 *        2. Thief - Avoid apprehension.
 *
 * Role switches at the beginning based on aa coin toss.
 * Outcomes:
 *      Police - Head
 *      Thief - Tail
 *
 * Actions:
 *      WASD movement
 *      Shooting
 *
 * Winning:
 * The winners is the last man standing.
 *
 * *************************************************************************************
*/

/*
 * AI - State Machine
 *    - Pathfinding (A* algorithm, Greedy Best First or Dijkstra)
 * PInput Handling
 * Rendering -
 *      Abstraction
 *      Text Rendering
 *      HUD - In game GUI (Buttons, Labels, CheckBoxes, RadioButtons, InputArea, ToggleButton, Slider, Panels, Frames
 *               GridLayout, BoxLayout(s), StackLayout, Widgets),
 *               Health Bar, Character Attributes and in game layout
 * Sound manager
 * Asset manager
 *
 * */

#include <iostream>

#include "papplication.h"
#include <window_events.h>
#include "ecs_service_conc.h"
#include "input.h"
#include "layer_service_conc.h"
#include "system_finder.h"

#include "assetdb_service_conc.h"
#include "renderer_service_conc.h"

using namespace isle_engine::math;
using namespace purity::ecs;
using namespace purity::graphics;

namespace purity{
    bool PApplication::verify()
    {
        return false;
    }

    void PApplication::process() {
        // Call the process method on all the services
        PInput::PollEvents();
        for (const auto runnable : serviceLocator->getRunnables())
        {
            runnable->process();
        }
    }

    void PApplication::update(float deltaTime) {
        // Call the update method on all the services
        for (const auto updatable : serviceLocator->getUpdatables())
        {
            updatable->update(1.0f);
        }
    }


    void PApplication::render() {
        const auto renderables = serviceLocator->getRenderables();
        for (const auto renderable : renderables)
        {
            renderable->preRender();
        }
        for (const auto renderable : renderables)
        {
            renderable->render();
        }
        for (const auto renderable : renderables)
        {
            renderable->postRender();
        }
    }

    void PApplication::preInit()
    {
        purity::PSystemFinder::application = this;
        // Set up window
        PWindow::bindWindowBackendAPI();
        window->createWindow(m_applicationInfo.width, m_applicationInfo.height, m_applicationInfo.title.c_str());
        PWindow::EventCallbackFunction boundCallback = [this](auto&& placeholder1) { onEvent(std::forward<decltype(placeholder1)>(placeholder1)); };
        window->setWindowsEventCallbacks(boundCallback);

        // Create all Services
        const auto ecsService = std::make_shared<PECSService>(window.get());
        const auto assetService = std::make_shared<assetDB::PAssetDatabase>();
        const auto layerService = std::make_shared<PLayerService>();
        const auto rendererService = std::make_shared<PRendererService>(window->getGLFWwindow());

        assetService->preInit(assetdbData);

        // Register Services
        serviceLocator->registerService<AECSService, PECSService>(ecsService);
        serviceLocator->registerService<AAssetDBService, assetDB::PAssetDatabase>(assetService);
        serviceLocator->registerService<ALayerService, PLayerService>(layerService);
        serviceLocator->registerService<ARendererService, PRendererService>(rendererService);
    }

    void PApplication::init() {
        // Call the init method on all the services
        for (const auto initializable : serviceLocator->getInitializables())
        {
            initializable->init();
        }

        // Scene layer must have been created now and attached will already be called
        // on it since its Pushed to stack on Init.
    }

    void PApplication::postInit()
    {
        for (const auto initializable : serviceLocator->getInitializables())
        {
            initializable->postInit();
        }
        // INFO: The default scene will be not nullptr after this point.
    }

    void PApplication::destroy() {
        // Call the destroy method on all the services
        window->deleteWindow();
        for (const auto terminable : serviceLocator->getTerminables())
        {
            terminable->destroy();
        }
    }

    void PApplication::exit() {
        // nothing for now
        PWindow::unbind();
        serviceLocator->unregisterService<ARendererService>();
        serviceLocator->unregisterService<ALayerService>();
        serviceLocator->unregisterService<AAssetDBService>();
        serviceLocator->unregisterService<AECSService>();
    }

    void PApplication::start() {
        for (const auto runnable : serviceLocator->getRunnables())
        {
            runnable->start();
        }
    }

    PApplication::PApplication()
    : serviceLocator(std::make_shared<PServiceLocator>())
    {
        window = std::make_shared<PWindow>();
    }

    void PApplication::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        // To close forward the WindowCloseEvent to the
        dispatcher.dispatch<WindowCloseEvent>(PURITY_BIND_EVENT_FN(PApplication::shouldClose)); // OR
        /*dispatcher.dispatch<WindowCloseEvent>([this](auto && placeholder1) {
            return shouldClose(std::forward<decltype(placeholder1)>(placeholder1));
        });*/
        const auto layerService = serviceLocator->getService<ALayerService, PLayerService>();
        for (auto it = layerService->m_layers.end(); it != layerService->m_layers.begin();) {
            const auto _tmp = (*--it);
            if (_tmp == nullptr) continue;
            (_tmp)->eventFired(event);
            if (event.getHandled())
            {
                std::cout << event;
                break;
            }
        }
    }

    bool PApplication::shouldClose(const WindowCloseEvent& event)
    {
        m_runningApp = false;
        return true;
    }
}
