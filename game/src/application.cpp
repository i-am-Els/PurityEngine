//
// Created by Eniola Olawale on 6/18/2024.
//

#include "application.h"

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

    triangle = new PEntity("Triangle");

    auto mesh = triangle->AddComponent<PMeshComponent>();
    PLog::echoValue(triangle->GetComponent<PTransformComponent>()->m_up);

//    std::unique_ptr<PShader> newOffsetShader = PShader::createShaders(
//            PShader::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_Inv_vert"]),
//            PShader::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_Inv_frag"])
//            );
}

void Application::destroy() {
    PApplication::destroy();
}

Application::Application(const std::string &title, int width, int height) : PApplication(title, width, height) {
    triangle = nullptr;
}

void Application::exit() {
    PApplication::exit();
    delete triangle;
}


