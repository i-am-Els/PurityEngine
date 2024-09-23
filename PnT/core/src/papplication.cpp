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

using namespace isle_engine::math;
using namespace pnt::ecs;

namespace pnt{

    void PApplication::process() {
        // Call the process method on all the services
        serviceLocator->getConcreteService<IECSService, PECSService>()->process();
        PInput::PollEvents();
    }

    void PApplication::update(float deltaTime) {
        // Call the update method on all the services
        serviceLocator->getConcreteService<IECSService, PECSService>()->update(1.0f);
    }

    void PApplication::render() {
        // Call the render method on all the services
        serviceLocator->getConcreteService<IECSService, PECSService>()->render();
    }

    void PApplication::init() {
        pnt::PSystemFinder::application = this;
        // Set up window
        PWindow::bindWindowBackendAPI();
        window = PWindow::createWindow(applicationInfo.width, applicationInfo.height, applicationInfo.title.c_str());

        // Create all Services
        auto ecsService = std::make_shared<PECSService>(window.get());
        auto layerService = std::make_shared<PLayerService>();

        // Register Services
        serviceLocator->registerService<IECSService>(ecsService);
        serviceLocator->registerService<ILayerService>(layerService);

        // Call the init method on all the services
        serviceLocator->getService<IECSService>()->init();

    }

    void PApplication::destroy() {
        // Call the destroy method on all the services

        serviceLocator->getService<IECSService>()->destroy();
    }

    void PApplication::exit() {
        // nothing for now
        PWindow::unbind();
    }

    void PApplication::start() {
        serviceLocator->getConcreteService<IECSService, PECSService>()->start();
    }
}
