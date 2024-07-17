//
// Created by Eniola Olawale on 6/18/2024.
//

#include "application.h"
#ifdef HACK_
#include "opengl_renderer.h"
#endif //HACK_

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

    quad = new PEntity("Triangle");

    auto mesh = quad->AddComponent<PMeshComponent>();
#ifdef HACK_
    dynamic_cast<POpenGLRenderSS*>(serviceLocator->getService<IRenderService>().get())->SetHackMesh(mesh->getVBO(), mesh->getEBO());
#endif //HACK_
    PLog::echoValue(quad->GetComponent<PTransformComponent>()->m_up);

//    std::unique_ptr<PShader> newOffsetShader = PShader::createShaders(
//            PShader::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_Inv_vert"]),
//            PShader::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_Inv_frag"])
//            );
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


