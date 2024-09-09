//
// Created by Eniola Olawale on 6/18/2024.
//

#include "application.h"

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

    quad = new PEntity("Quad");

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
    delete quad;
}



