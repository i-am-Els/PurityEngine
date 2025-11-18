//
// Created by Eniola Olawale on 6/18/2024.
//

#include "application.h"
#include "quad_comp.h"

using namespace purity;

void Application::render() {
    PApplication::render();
}

void Application::process() {
    PApplication::process();
}

void Application::update(float deltaTime) {
    PApplication::update(deltaTime);
}

void Application::init() {
    PApplication::init();
    //
    // auto quad = Scene.CreateEntity("Quad");
    //
    // auto mesh = quad.AddComponent<PMeshComponent>();
    // auto render = quad.AddComponent<PRenderComponent>();
    //
    //
    // PLog::echoValue(quad.GetComponent<PTransformComponent>()->m_up); // Segfault here too, transform is null

}

void Application::start() {
    PApplication::start();
}

void Application::destroy() {
    PApplication::destroy();
}

Application::Application() : PApplication() {

}

void Application::exit() {
    PApplication::exit();
}

purity::PApplication* purity::CreateApplication(){
    return new Application();
}

