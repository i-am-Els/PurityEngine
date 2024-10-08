//
// Created by Eniola Olawale on 6/18/2024.
//

#include "application.h"
#include "quad_comp.h"

using namespace pnt;

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

    quad = Scene.CreateEntity("Quad");

    auto mesh = quad->AddComponent<PMeshComponent>();
    auto render = quad->AddComponent<PRenderComponent>();


    PLog::echoValue(quad->GetComponent<PTransformComponent>()->m_up); // Segfault here too, transform is null

}

void Application::start() {
    PApplication::start();
}

void Application::destroy() {
    PApplication::destroy();
}

Application::Application(const std::string &title, int width, int height) : PApplication(title, width, height) {
    quad = nullptr;
}

void Application::exit() {
    PApplication::exit();
}

pnt::PApplication* pnt::CreateApplication(){
    return new Application("PnT", 700, 500);
}

