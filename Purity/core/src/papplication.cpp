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

#include "system_finder.h"
#include "papplication.h"
#include "input.h"
#include "ecs_service_conc.h"
#include "layer.h"
#include <window_events.h>

#include "assetdb_service_conc.h"

using namespace isle_engine::math;
using namespace purity::ecs;

namespace purity{
    bool PApplication::verify()
    {
        return false;
    }

    void PApplication::process() {
        // Call the process method on all the services
        for (const auto runnable : serviceLocator->getRunnables())
        {
            runnable->process();
        }
        PInput::PollEvents();
    }

    void PApplication::update(float deltaTime) {
        // Call the update method on all the services
        for (const auto updatable : serviceLocator->getUpdatables())
        {
            updatable->update(1.0f);
        }
    }

    void PApplication::render() {
        for (const auto renderable : serviceLocator->getRenderables())
        {
            renderable->render();
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
        const auto layerService = std::make_shared<PLayerService>();
        const auto assetService = std::make_shared<assetDB::PAssetDatabase>();

        assetService->preInit(assetdbData);

        // Register Services
        serviceLocator->registerService<PECSService>(ecsService);
        serviceLocator->registerService<PLayerService>(layerService);
        serviceLocator->registerService<assetDB::PAssetDatabase>(assetService);
    }

    void PApplication::init() {
        // Call the init method on all the services
        for (const auto initializable : serviceLocator->getInitializables())
        {
            initializable->init();
        }
    }

    void PApplication::postInit()
    {
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
        serviceLocator->unregisterService<assetDB::PAssetDatabase>();
        serviceLocator->unregisterService<PLayerService>();
        serviceLocator->unregisterService<PECSService>();
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
        window = std::make_unique<PWindow>();
    }

    void PApplication::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        // To close forward the WindowCloseEvent to the
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&PApplication::shouldClose, this, std::placeholders::_1)); // OR
        /*dispatcher.dispatch<WindowCloseEvent>([this](auto && placeholder1) {
            return shouldClose(std::forward<decltype(placeholder1)>(placeholder1));
        });*/
        const auto layerService = serviceLocator->getService<PLayerService>();
        for (auto it = layerService->layerStack.end(); it != layerService->layerStack.begin();) {
            auto _tmp = (*--it);
            if (_tmp == nullptr) continue;
            (_tmp)->eventFired(event);
            if (event.getHandled()) break;
        }
        std::cout << event;
    }

    bool PApplication::shouldClose(const WindowCloseEvent& event)
    {
        m_runningApp = false;
        return true;
    }
}
