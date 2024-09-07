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

//    try{
//        auto item = dynamic_cast<PECSService *>(serviceLocator->getService<IECSService>().get());
//        if (item == nullptr)
//            throw "Invalid Service";
//        auto r = PECSService::s_getSystem<PRenderComponent>();
//        auto renderer = dynamic_cast<POpenGLRenderSS*>(r);
//        renderer->SetUpBuffers(mesh->getVBO(), mesh->getEBO());   // TODO - Prevent segfault caused because mesh is null at this point.
//        // TODO - Implement the mesh systems functions for all Manipulative Behaviours
//    }catch(const char* msg){
//        std::cerr << "Error: " << msg << std::endl;
//    }
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



